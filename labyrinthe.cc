#include "box2d.hh"
#include "partial_box2d.hh"

#include "box2d_iterator.hh"
#include "partial_box2d_iterator.hh"

#include "image2d.hh"
#include "partial_image2d.hh"

#include "neighb2d_iterator.hh"
#include "point2d.hh"

#include <iostream>
#include <queue>
#include <limits>

//******************************************************************************************************

/* Compute the distance map */

template <typename I> // I : image2d ou partial_image2d
I compute_distance_map(const I& input)
{
    // these 4 new lines below express that some types depends on I
    // and on domain_type (that is, I::domain_type)
    using point_type      = typename I::point_type;
    using domain_type     = typename I::domain_type;
    using p_iterator_type = typename domain_type::p_iterator_type;
    using n_iterator_type = typename domain_type::n_iterator_type; //neighborhood

    // Initialisations
    const domain_type& domain = input.get_domain(); // instead of: box2d D = input.domain();
    const unsigned max = std::numeric_limits<int>::max();
    I distance_map(domain); // bounding_box always return a box2d type // instead of: image2d<unsigned> distance_map(D);
    distance_map.fill_with_one_value(max, distance_map.get_domain().get_nbpoints());
    p_iterator_type p(domain); //create a box iterator object    // instead of: box2d_iterator p(D);

    const point_type tmp_point(0,0);
    auto n = n_iterator_type(tmp_point);// neighb2d_iterator n;
    std::queue<point_type> q;

    for (point_type current_pt = p.start(); p.is_valid() ; current_pt =  p.next())
    {
        if (input[current_pt] == 1)
        {
            distance_map[current_pt] = 0;
            n.center_at(current_pt);
            for (point_type current_neighbor = n.start() ; n.is_valid() ; current_neighbor = n.next())
            {
                if (domain.has(current_neighbor))
                {
                    if (input[current_neighbor] == 0)
                    {
                        q.push(current_pt);
                        break;
                    }
                }
            }
        }
    }


    while (!q.empty())
    {
        point_type front_pt = q.front();
        q.pop(); // queue : first in, first out FIFO
        n.center_at(front_pt);

        for (point_type current_neighbor = n.start() ; n.is_valid() ; current_neighbor = n.next())
        {
            if (domain.has(current_neighbor))
            {
                if (distance_map[current_neighbor] == max)
                {
                    distance_map[current_neighbor] = distance_map[front_pt] + 1 ;
                    q.push(current_neighbor);
                }
            }
        }
    }

    return distance_map;
} // end compute_distance_map


//******************************************************************************************************

/* Compute the labyrinth solution / a path between 2 points */

template <typename I>
bool labyrinth(const I& rect_img)
{
    std::cout << "Input: \n" << rect_img;

    /* STEP 1: Where are the starting and ending points ? */

    auto p = project_namespace::box2d::p_iterator_type(rect_img.get_domain());
    project_namespace::point2d start_pt(0,0);
    project_namespace::point2d end_pt(0,0);

    // look for the start (value = 2) point and the end (value = 3) point
    // and memorize their position
    for (project_namespace::point2d current_pt = p.start() ; p.is_valid() ; current_pt = p.next())
    {
            if(rect_img[current_pt] == 2)
            {
                start_pt.set_coords(current_pt.get_row(),current_pt.get_col() );
            }
            else if(rect_img[current_pt] == 3)
            {
                end_pt.set_coords(current_pt.get_row(),current_pt.get_col() );
            }
    }

    //-------------------------------------------------------

    /* STEP 2 : Create the partial image and set it (value change) */

    const project_namespace::partial_box2d partial_box(rect_img);
    project_namespace::partial_image2d<int> partial_img(partial_box); //create partial image

    std::vector<int> tmp_values;
    int i=0;
    for(int val : rect_img.get_data())
    {
        if(val != 0) // keep non-null values
        {
            tmp_values.resize(i+1);
            tmp_values[i] = val;
            ++i;
        }
    }

    for(unsigned j=0 ; j<tmp_values.size() ; ++j)
    {
        if (tmp_values[j] == 2) // set all "2" values to 1 (normally there is only 1 starting point)
        {
            tmp_values[j] = 1;
        }
        else // set all other values (1 and 3) to 0
        {
            tmp_values[j] = 0;
        }
    }

    partial_img.fill_with(tmp_values);


    //-------------------------------------------------------

    /* STEP 3 : Compute distance map for the partial image. */

    project_namespace::partial_image2d<int> distance_map = compute_distance_map(partial_img);


    //-------------------------------------------------------

    /* STEP 4 : Find the way/path (how to go from the starting point to the ending point) */

    auto path_img(distance_map);
    path_img[end_pt] = 1;
    project_namespace::point2d current_pt = end_pt;
    project_namespace::point2d previous_pt = end_pt;
    project_namespace::box2d::n_iterator_type n_it(end_pt);

    while(current_pt.get_row() != start_pt.get_row() || current_pt.get_col() != start_pt.get_col())
    {
        previous_pt = current_pt;
        int val = distance_map[current_pt];
        n_it.center_at(current_pt);
        for(project_namespace::point2d current_neighbor = n_it.start() ; n_it.is_valid() ; current_neighbor = n_it.next())
        if(distance_map.get_domain().has(current_neighbor))
        {
            if(distance_map[current_neighbor] == val-1)
            {
                previous_pt = current_pt;
                current_pt = current_neighbor;
                path_img[current_neighbor] = 1;
            }
        }

        if(current_pt.get_row() == previous_pt.get_row() && current_pt.get_col() == previous_pt.get_col())
        {
            std::cout << "\nSorry,no solution found for the input labyrinth.\n";
            return false;
        }
    }
    path_img[start_pt] = 1;

    //-------------------------------------------------------

    // ETAPE 5: Construct a "clear" partial image with the path

    project_namespace::image2d<unsigned> rect_path_solution(rect_img.get_domain());
    rect_path_solution.fill_with_one_value(0,rect_img.get_domain().get_nbpoints());

    project_namespace::partial_box2d::p_iterator_type p5(path_img.get_domain());
    for(project_namespace::point2d current_pt = p5.start() ; p5.is_valid() ; current_pt = p5.next())
    {
        if(path_img[current_pt] == 1)
        {
            rect_path_solution[current_pt] = 1;
        }
    } // here, we have a map full of 1 (if the point is part of the solution path) and 0 (if the point is not part of the solution path)

    // Construct final partial image from rect_path_solution (image2 type)
    const project_namespace::partial_box2d partial_box_path_solution(rect_path_solution);
    project_namespace::partial_image2d<int> partial_img2d_path_solution(partial_box_path_solution);
    partial_img2d_path_solution.fill_with_one_value(1, partial_box_path_solution.get_nbpoints());
    std::cout << "\nOutput: \n" << partial_img2d_path_solution << '\n';

    return true ;
}




int main()
{

    std::cout << "\n DISTANCE MAP - RECTANGULAR IMAGE :\n\n";
    const int values[] = {  0, 0, 0, 0, 0,
                            0, 0, 0, 1, 0,
                            0, 0, 1, 1, 0,
                            0, 0, 0, 1, 0,
                            1, 0, 0, 1, 0,
                            0, 0, 0, 1, 0,};

    const project_namespace::point2d first_point(0,0), last_point(5,4);
    const project_namespace::box2d D(first_point, last_point);
    project_namespace::image2d<int> input(D);

    input.fill_with(values);
    auto result = compute_distance_map(input);
    std::cout << "Input : \n" << input << "\n Output: \n" << result << '\n';



    std::cout << "\n-----------------------------------------------------\n";
    std::cout << "\n DISTANCE MAP - NON RECTANGULAR IMAGE :\n\n";
    const int m_values[] = { 1, 1, 1, 1, 0,
                             0, 0, 0, 1, 0,
                             0, 1, 1, 1, 0,
                             0, 1, 0, 1, 0,
                             1, 1, 0, 0, 0,
                             0, 1, 1, 1, 1 };

    const project_namespace::point2d p_first_point(0,0), p_last_point(5,4);
    const project_namespace::box2d p_D(p_first_point, p_last_point);
    project_namespace::image2d<unsigned> img2d_test(p_D);

    img2d_test.fill_with(m_values);


    // Initialisation
    const project_namespace::partial_box2d p_box(img2d_test);
    project_namespace::partial_image2d<int> p_input(p_box);

    // Fill partial image
    const int p_values[] = { 1, 0, 0, 0,
                                      0,
                                0, 0, 0,
                                0,    0,
                            0, 0,
                                0, 0, 0, 0 };
    p_input.fill_with(p_values);
    auto p_result = compute_distance_map(p_input);
    std::cout << "Input: \n" << p_input << "\nOutput: \n" << p_result << '\n';



 /* LABYRINTH*/

    std::cout << "\n-----------------------------------------------------\n";
    std::cout << "LABYRINTH - EXAMPLE 1 - SOLUTION POSSIBLE\n\n";

    const project_namespace::point2d lab_first_point(0,0), lab_last_point(5,4);
    const project_namespace::box2d lab_D(lab_first_point, lab_last_point);
    project_namespace::image2d<unsigned> rect_img(lab_D);
    const int lab_m_values[] = { 2, 1, 1, 1, 0,
                                0, 0, 0, 1, 0,
                                0, 1, 1, 1, 0,
                                0, 1, 0, 1, 0,
                                1, 1, 0, 0, 0,
                                0, 1, 1, 1, 3 };
    rect_img.fill_with(lab_m_values);
    labyrinth(rect_img);


    std::cout << "\n----\n";
    std::cout << "LABYRINTH - EXAMPLE 2 - SOLUTION IMPOSSIBLE\n\n";

    project_namespace::image2d<unsigned> rect_img_bis(lab_D);
    const int lab_m_values_bis[] = { 2, 1, 1, 1, 0,
                                    0, 0, 0, 1, 0,
                                    0, 0, 0, 0, 0,
                                    0, 1, 0, 1, 0,
                                    1, 1, 0, 0, 0,
                                    0, 1, 1, 1, 3 };
    rect_img_bis.fill_with(lab_m_values_bis);
    labyrinth(rect_img_bis);
    return 0;
}
