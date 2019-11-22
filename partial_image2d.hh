#ifndef PARTIAL_IMAGE2D_HH
#define PARTIAL_IMAGE2D_HH

#include <iostream>
#include <vector>
#include <limits> // assert member function
#include <assert.h>
#include "box2d.hh"
#include "point2d.hh"
#include "image2d.hh"
#include "partial_box2d.hh"


namespace project_namespace
{
    template <typename T>
    class partial_image2d
    {
        public:

            using value_type = T;
            using point_type = point2d;
            using domain_type = partial_box2d;


            //***********************************************************************
            /* CONSTRUCTORS AND DESTRUCTORS */

            partial_image2d(const domain_type& domain)
            : domain_(domain)
            {
            }

            ~partial_image2d()
            {
            }

            //***********************************************************************
            /* MEMBER FUNCTIONS */

            /*Fill the image2d */

            template <typename U, unsigned n>
            void fill_with(U(&values)[n])
            {
                assert(domain_.get_nbpoints() == n); // check if domain_ and the image2d have the same box2d size
                data_.resize(n);
                for (unsigned i=0; i<data_.size(); ++i) // ++i means "increment i immediately" while i++ means "use the old value of i for now but increment i later"
                {
                    data_[i] = values[i];
                }
            }

            /* Fill with one value */
            void fill_with_one_value(value_type value, unsigned n)
            {
                assert(domain_.get_nbpoints() == n); // check if domain_ and the image2d have the same box2d size
                data_.resize(n);
                for (unsigned i=0; i<data_.size(); ++i) // ++i means "increment i immediately" while i++ means "use the old value of i for now but increment i later"
                {
                    data_[i] = value;
                }
            }


            /* Fill with a std::vector (Level 6) */
           template <typename U>
            void fill_with(std::vector<U> &values)
            {
                assert(domain_.get_nbpoints() == values.size());
                data_.resize(values.size());
                for (unsigned i = 0 ; i < data_.size() ; ++i)
                {
                data_[i] = values[i];
                }
            }



            //***********************************************************************
            /* OPERATORS */

            T& operator[](const point_type& pt) // read-write setter
            {
                assert(domain_.has(pt)); // check if the point is in the domain
                std::vector<point2d> pts_list = domain_.get_domain();

                int i = 0 ;
                for (point2d p : pts_list) // do a research by i/j index value, can't use .at() directly
                {
                    if(p.get_row() != pt.get_row() || p.get_col() != pt.get_col())
                    {
                         i = i + 1;
                    }
                    else
                    {
                        break;
                    }
                }
                return data_[i];
            }



            T operator[](const point_type& pt) const // read only setter
            {
                assert(domain_.has(pt)); // check if the point is in the domain
                std::vector<point2d> pts_list = domain_.get_domain();

                int i = 0 ;
                for (point2d p : pts_list) // do a research by i/j index value, can't use .at() directly
                {
                    if(p.get_row() != pt.get_row() || p.get_col() != pt.get_col())
                    {
                        i = i + 1 ;
                    }
                    else
                    {
                        break;
                    }
                }
                return data_[i];
            }


            //***********************************************************************
            /* GETTERS AND SETTERS */

            std::vector<T> get_data() const
            {
                return data_;
            }

            domain_type get_domain() const
            {
                return domain_;
            }

            box2d get_bounding_box() const
            {
                return domain_;
            }


        // end public functions

        private:
            partial_box2d domain_;
            std::vector<T> data_;
    }; // end class point2d




    //***********************************************************************
    /* PRINTING */

    template <typename T>
    std::ostream &operator<<(std::ostream &ostr, const partial_image2d<T> &img)
    {
        image2d<unsigned> image = img.get_domain().get_img();
        box2d b = image.get_domain();
        unsigned nbrows = b.get_nbrows();
        unsigned nbcols = b.get_nbcols();
        for (unsigned i = 0; i < nbrows; ++i)
        {
            for (unsigned j = 0; j < nbcols; ++j)
            {
                point2d pt(i, j);
                if (image[pt] == 0)
                {
                    ostr << ' ';
                }

                else
                {
                    ostr << img[pt];
                }
                ostr << ' ';
            }
            ostr << '\n';
        }
        return ostr;
    }
}


#endif
