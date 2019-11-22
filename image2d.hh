#ifndef IMAGE2D_HH
#define IMAGE2D_HH

#include <iostream>
#include <vector>
#include <limits>
#include <assert.h>

#include "box2d.hh"
#include "point2d.hh"

namespace project_namespace
{
    template<typename T> // type will be specialized at compilation
    class image2d
    {
        public:
            using value_type = T; // compile with --std=c++11 in order to use the using
            using point_type = point2d;
            using domain_type = box2d;

            //***********************************************************************
            /* CONSTRUCTORS AND DESTRUCTORS */

            image2d(const domain_type& domain)
            : domain_(domain)
            {
            }

            ~image2d()
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
                    data_.at(i) = values[i];
                }
            }


            /* Fill with a std::vector (Level 8) */
            template<unsigned n>
            void fill_with(unsigned (&values)[n])
            {
                assert(domain_.get_nbpoints() == n);
                data_.resize(n);
                for (unsigned i = 0 ; i < data_.size() ; ++i)
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
                    data_.at(i) = value;
                }
            }


            //***********************************************************************
			/* GETTERS AND SETTERS */

            box2d get_bounding_box() const
            {
                return domain_; // will always return a box2d, even for images which are not "image2d" type            }
            }

            const domain_type& get_domain() const
            {
                return domain_;
            }


            std::vector<T> get_data() const
            {
                return data_;
            }


            //***********************************************************************
			/* OPERATORS */

            T& operator[](const point_type& pt) // read-write setter
            {
                assert(domain_.has(pt)); // check if the point is in the domain1
                int r = pt.get_row();
                int c = pt.get_col();
                
                unsigned nbcols = domain_.get_nbcols();
                return data_[r*nbcols + c]; // because data is a std::vector
            }


            T operator[](const point_type& pt) const // read only setter
            {
                assert(domain_.has(pt)); // check if the point is in the domain2
                int r = pt.get_row();
                int c = pt.get_col();

                unsigned nbcols = domain_.get_nbcols();
                return data_[r*nbcols + c]; // because data is a std::vector
            }



        // end public functions

        private:
            box2d domain_;
            std::vector<T> data_; // T cannot be bool; use bool_t
    }; // end class point2d



    //***********************************************************************
	/* PRINTING */

    template<typename T>
    std::ostream& operator<<(std::ostream& ostr, const image2d<T>& img)
    {
        box2d b = img.get_domain();
        unsigned nbrows = b.get_nbrows();
        unsigned nbcols = b.get_nbcols();
        for (unsigned i = 0; i < nbrows; ++i)
        {
        for (unsigned j = 0; j < nbcols; ++j)
        {
            point2d pt(i,j);
            ostr << img[pt];
        ostr << ' ';
        }
        ostr << '\n';
        }
        return ostr;
    }


}

#endif


