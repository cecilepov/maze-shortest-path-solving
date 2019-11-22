#ifndef BOX2D_ITERATOR_HH
#define BOX2D_ITERATOR_HH

#include "point2d.hh"
#include "box2d.hh"

namespace project_namespace
{
    class box2d_iterator
    {
        public:

            //***********************************************************************
            /* CONSTRUCTORS AND DESTRUCTORS */

            /* Constructor of the class box2d_iterator */
            box2d_iterator(const box2d& domain, const point2d& pt)
            : domain_(domain)
            , current_pt_(pt)
            {
            }

            box2d_iterator(const box2d& domain)
            // : domain_(domain) //box2d_iterator(domain, domain.get_start_pt())
            // , current_pt_(domain.get_start_pt())
            : box2d_iterator(domain, domain.get_start_pt())
            {
            }

            ~box2d_iterator()
            {
            }


           
            //***********************************************************************
            /* MEMBER FUNCTIONS */

            /* Member functions for iteration */

            point2d start() const
            {
                return domain_.get_start_pt();
            }


            point2d next()
            {
                int r = current_pt_.get_row();
                int c = current_pt_.get_col();

                // Increment coordinates, and check if they are in the domain
                int new_r = r + 1;
                int new_c = c + 1;

                if (new_c > domain_.get_end_pt_col()) //column out of domain
                {
                    if (!(new_r > domain_.get_end_pt_row())) // row still in domain
                    {
                        new_c = domain_.get_start_pt_col(); // next row,first column (left)
                    }
                    current_pt_ = point2d(new_r, new_c); //if out of domain, will be checked by is_valid function
                    current_pt_.set_coords(new_r, new_c); //if out of domain, will be checked by is_valid function
                }

                else // column still in domain
                {
                    current_pt_.set_coords(r, new_c); // point on the right
                }
                return current_pt_;
            }


            bool is_valid() const
            {
                return domain_.has(current_pt_); //true if the point in included in the domain
            }


            //***********************************************************************
            /* GETTERS AND SETTERS */

            point2d get_current_pt() const
            {
                return current_pt_;
            }


            box2d get_domain() const
            {
                return domain_;
            }
        
        
        private:
            box2d domain_;
            point2d current_pt_;
    };

}

#endif




