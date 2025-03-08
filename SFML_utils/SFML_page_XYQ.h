#ifndef SFML_page_XYQ_H
#define SFML_page_XYQ_H

#include "SFML_obj_XYQ.h"


#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>


using namespace std;



class SFML_page_XYQ{


public:

    SFML_page_XYQ();

// ====================================================================== >>>>>
//      Functionalities
// ====================================================================== >>>>>

    /* 
    Add a new object to the vector.
    NOTE 1: Instances of child classes to the polymorphic parent class SFML_obj_XYQ will be 
    converted to the parent class.
    */
    void addObj( shared_ptr<SFML_obj_XYQ> newObj );

    /*
    Update all objects in the page.
    NOTE: if objects on the same page have inter-dependence, this function is not going
    to adjust for correct order of updating. This function simply goes through 1st to last
    added entry to the list of objects.
    */
    void update();

    /*
    Drawn all objects on this page on the SFML window.
    NOTE: there is no order of drawing by default.
    */
    void beDrawn( sf::RenderWindow &window ) const;

    /*
    Delete the target page object.
    NOTE 1: It is expected that no two pointers are the same in the vector, so only one
    match/delete is to be expected.
    NOTE 2: Only the pointer in the page's vector is deleted given match is found.
    */
    void delTarObj( const shared_ptr<SFML_obj_XYQ> tarObj );
// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

    void enable();
    void disable();
    void toggleEnable();
    bool isEnabled() const;

// ====================================================================== <<<<<

protected:

private:

    // Flag indicating whether this page is enabled.
    bool enabled = false;

    // Vector of SFML drawable objects belonging to this page.
    vector< shared_ptr<SFML_obj_XYQ> > SFML_objs_vec;

    // Vector saving the enabled/disabled states of the objects when the page
    // turns off.
    vector< bool > enableStatus_vec;

};




#endif // SFML_page_XYQ_H


/*
DONE: Create a vector of boolean matching in size to the vector of SFML objects of the
page. The booleans represent the enable/disable state of each SFML object of matching index.

This boolean vector is updated when the page becomes disabled right before all SFML objects
are disabled.
This boolean vector is then used once more to restore all previous enable/disable states of the
objects when the page becomes enabled again.
*/

