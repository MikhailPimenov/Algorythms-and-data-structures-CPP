#include "there_is_collision_between_arc_and_circle.h"


bool there_is_collision_between_arc_and_circle(const Arc& arc, const Circle& circle) {

    const double distance = get_distance(arc.m_owner->m_center, circle.m_center);
    

    if (distance > arc.m_owner->m_radius + circle.m_radius ||               // arc and circle not intersect 
        arc.m_owner->m_radius > distance + circle.m_radius ||               // circle is deep inside arc and does not touch arc 
        are_equal(arc.m_owner->m_radius, distance + circle.m_radius))       // circle is inside arc, but touches it
        return false;


    // circle covers circumference of arc's owner

    const double angle_b = get_angle_with_x_axis(arc.m_b, arc.m_owner->m_center);
    const double angle = get_angle_with_x_axis(circle.m_center, arc.m_owner->m_center);
    const double angle_a = get_angle_with_x_axis(arc.m_a, arc.m_owner->m_center);
  
    // considering angles only from 0 to 2*pi
    const double angle_a_rotated = angle_a > angle_b ?
        angle_a - angle_b : 2.0 * g_pi + angle_a - angle_b;
    const double angle_b_rotated = 0.0;
    const double angle_rotated = angle > angle_b ?
        angle - angle_b : 2.0 * g_pi + angle - angle_b;


    // circle is from the side of arc
    if (is_between(angle_rotated, angle_a_rotated, angle_b_rotated))
        return true;

    // circle covers one of arc's ends
    if (get_distance(arc.m_a, circle.m_center) > circle.m_radius &&
        get_distance(arc.m_b, circle.m_center) > circle.m_radius)
        return false;

    return true;
}