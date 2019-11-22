#ifndef POINT2D_HH
#define POINT2D_HH

#include <iostream>
#include <vector>
#include <limits>

namespace project_namespace
{
    class point2d
    {
        public:

            //***********************************************************************
            /* CONSTRUCTORS AND DESTRUCTORS */
        
            /* Constructor of class point2d */
            point2d(int row, int column)
            : row_(row)
            , col_(column)
            {
            }

            /* Default constructor */
            point2d()
            {
                row_ = 0;
                col_ = 0;
            }

            /* Destructor of class box2d */
            ~point2d()
            {
            }
            
            //***********************************************************************
            /* GETTERS AND SETTERS */

            int get_row() const // const member functions cannot modify any data members of a class
            {
                return row_;
            }

            int get_col() const 
            {
                return col_;
            }

            void set_row(const int new_row)
            {
                row_ =  new_row;
            }

            void set_col(const int new_column)
            {
                col_ =  new_column;
            }

            void set_coords(const int new_row, const int new_column)
            {
                set_row(new_row);
                set_col(new_column);
            }

        // end public functions

        private:
            int row_;
            int col_;

    }; // end class point2d
}

#endif
