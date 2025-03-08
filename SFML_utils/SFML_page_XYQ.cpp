#include "SFML_page_XYQ.h"




SFML_page_XYQ::SFML_page_XYQ(){

}


// ====================================================================== >>>>>
//      Functionalities
// ====================================================================== >>>>>

void SFML_page_XYQ::addObj( shared_ptr<SFML_obj_XYQ> newObj ){
    this->SFML_objs_vec.push_back( newObj );
    this->enableStatus_vec.push_back( newObj->isEnabled() );
}


void SFML_page_XYQ::update(){
    //for( shared_ptr<SFML_obj_XYQ> currPtr : SFML_objs_vec ){
    //    currPtr->update();
    //}
    for( unsigned int i = 0; i < SFML_objs_vec.size(); i++ ){
        SFML_objs_vec.at(i)->update();
        enableStatus_vec.at(i) = SFML_objs_vec.at(i)->isEnabled();
    }
}


void SFML_page_XYQ::beDrawn( sf::RenderWindow &window ) const{

    if( enabled ){
        for( shared_ptr<SFML_obj_XYQ> currPtr : SFML_objs_vec ){
            currPtr->beDrawn( window );
        }
    }
    
}


void SFML_page_XYQ::delTarObj( const shared_ptr<SFML_obj_XYQ> tarObj ){

    for( unsigned int i = 0; i < this->SFML_objs_vec.size(); i++ ){

        if(  tarObj == SFML_objs_vec.at(i) ){
            SFML_objs_vec.erase( SFML_objs_vec.begin() + i );
            return;
        }

    }

    throw std::runtime_error( "No matching pointer to delete." );

}

// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

void SFML_page_XYQ::enable(){
    this->enabled = true;
    // Restore the enable status from previous records.
    for( unsigned int i = 0; i < SFML_objs_vec.size(); i++ ){
        enableStatus_vec.at(i) ? SFML_objs_vec.at(i)->enable() : SFML_objs_vec.at(i)->disable();
    }
}

void SFML_page_XYQ::disable(){
    this->enabled = false;
    // Record the enable status from all objects and disable them.
    for( unsigned int i = 0; i < SFML_objs_vec.size(); i++ ){
        enableStatus_vec.at(i) = SFML_objs_vec.at(i)->isEnabled();
        SFML_objs_vec.at(i)->disable();
    }
}

void SFML_page_XYQ::toggleEnable()
    {this->enabled = !this->enabled;}

bool SFML_page_XYQ::isEnabled() const
    {return this->enabled;}

// ====================================================================== <<<<<

