#ifndef PARTIAL_BOX2D_ITERATOR_HH
#define PARTIAL_BOX2D_ITERATOR_HH

#include <iostream>
#include <vector>
#include <limits> // assert member function


#include "point2d.hh"
#include "partial_box2d.hh"


namespace project_namespace
{

    class partial_box2d_iterator
    {
        public:

        //***********************************************************************
        /* CONSTRUCTORS AND DESTRUCTORS */

        partial_box2d_iterator(const partial_box2d& img_partial_box2d, const unsigned position)
        : img_partial_box2d_(img_partial_box2d)
        , current_pos_(position)
        {  
        }

        partial_box2d_iterator(const partial_box2d& img_partial_box2d)
        // : img_partial_box2d_(img_partial_box2d)
        // , current_pos_(0)
        : partial_box2d_iterator{img_partial_box2d, 0}
        {
        }

        ~partial_box2d_iterator()
        {
        }


        //***********************************************************************
        /* MEMBER FUNCTIONS */

        point2d start() const
        {
            return img_partial_box2d_.get_start_point();
        }


        point2d next() 
        {
            current_pos_ = current_pos_ +1 ;
            return this->get_current_point();
        }

        bool is_valid()
        {
            std::vector<point2d> partial_domain = img_partial_box2d_.get_domain();
            return current_pos_ < partial_domain.size();
        }


        //***********************************************************************
         /* GETTERS AND SETTERS */ 

        point2d get_current_point() const
        {
            std::vector<point2d> partial_domain = img_partial_box2d_.get_domain();
            return partial_domain[current_pos_];
        }


        // end public functions

        private:
            partial_box2d img_partial_box2d_;
            unsigned current_pos_; // index in the std::vector
    }; // end class
}

#endif


