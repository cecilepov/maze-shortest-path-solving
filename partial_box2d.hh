#ifndef PARTIAL_BOX2D_HH
#define PARTIAL_BOX2D_HH

#include <iostream>
#include <vector>
#include <limits> // assert member function

#include "box2d.hh"
#include "point2d.hh"
#include "image2d.hh"


namespace project_namespace
{
    class partial_box2d_iterator;
    class neighb2d_iterator;

    class partial_box2d
    {
        public:
            using p_iterator_type = partial_box2d_iterator;
            using n_iterator_type = neighb2d_iterator;

            //***********************************************************************
            /* CONSTRUCTORS AND DESTRUCTORS */

            partial_box2d(const image2d<unsigned>& img)
            : img_(img)
            {
            }

            ~partial_box2d()
            {
            }

           //***********************************************************************
            /* MEMBER FUNCTIONS */

            /*Check if a point is in defined domain*/
            bool has(const point2d& pt) const
            {
                if(img_.get_domain().has(pt))
                {
                    if (img_[pt] == 0)
                    {
                        return false ;
                    }
                    else
                    {
                        return true ;
                    }
                }
                else // not in the defined domain
                {
                    return false;
                }
            }

            /* return list of points not equal to 0 */

            std::vector<point2d> get_domain() const //
            {
                std::vector<point2d> partial_domain;
                box2d img_domain = img_.get_domain();

                unsigned nb_rows = img_domain.get_nbrows();
                unsigned nb_cols = img_domain.get_nbcols();

                for (unsigned i =0; i< nb_rows ; i++)
                {
                    for (unsigned j = 0 ; j < nb_cols ; j++)
                    {
                        point2d pt_ij(i,j);
                        if (img_[pt_ij] != 0)
                        {
                            partial_domain.push_back(pt_ij);
                        }
                    }
                }
                return partial_domain;
            }

            //***********************************************************************
            /* GETTERS ANDD SETTERS */

            image2d<unsigned> get_img() const
            {
                return img_;
            }

            unsigned get_nbpoints() const
            {
                std::vector<point2d> partial_domain = this->get_domain();
                return partial_domain.size();

            }

            point2d get_start_point() const
            {
                std::vector<point2d> partial_domain = this->get_domain();
                return partial_domain.front(); //access first element
            }

            point2d get_end_point() const
            {
                std::vector<point2d> partial_domain = this->get_domain();
                return partial_domain.back(); //access last element
            }

        // end public functions

        private:
            image2d<unsigned> img_;
    }; // end class point2d
}

#endif
