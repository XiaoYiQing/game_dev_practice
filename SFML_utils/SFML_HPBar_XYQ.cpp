#include "SFML_HPBar_XYQ.h"


// ====================================================================== >>>>>
//      Constructor
// ====================================================================== >>>>>

SFML_HPBar_XYQ::SFML_HPBar_XYQ():
    SFML_obj_XYQ()
{

    infoBox = SFML_TxtBox_XYQ( sf::Font(), "HP" );
    
    this->update();

}


// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Functionalities
// ====================================================================== >>>>>

void SFML_HPBar_XYQ::update(){

    // Update the HP bar general position using the fullbar as the primary 
    // position reference.
    this->position;
    fb_p_d[0] = position.x;
    fb_p_d[1] = position.y;

    this->fb_outl_thick;
    this->db_outl_thick;

    // Update the full bar.
    this->fullBar.setPosition( this->fb_p_d[0] + fb_outl_thick, 
        this->fb_p_d[1] + fb_outl_thick );
    this->fullBar.setSize( sf::Vector2f( fb_p_d[2], fb_p_d[3] ) );
    this->fullBar.setFillColor( this->fb_color );
    this->fullBar.setOutlineThickness( this->fb_outl_thick );
    this->fullBar.setOutlineColor( this->fb_outl_color );

    // The position of the dynamic bar is updated.
    this->db_p_d[0] = this->fb_p_d[0] + this->in_marg;
    this->db_p_d[1] = this->fb_p_d[1] + this->in_marg;
    // The width of the dynamic bar is updated w.r.t. current health.
    float max_dp_width = this->fb_p_d[2] - 2.0f*this->in_marg;
    float HP_ratio = this->HPnum[1] / this->HPnum[0];
    this->db_p_d[2] = max( 0.0f, HP_ratio*max_dp_width );
    // The height of the dynamic bar is updated.
    this->db_p_d[3] = this->fb_p_d[3] - 2.0f*this->in_marg;

    // Update the dynamic bar.
    this->dynamBar.setPosition( this->db_p_d[0] + fb_outl_thick, 
        this->db_p_d[1] + fb_outl_thick );
    this->dynamBar.setSize( sf::Vector2f( this->db_p_d[2], this->db_p_d[3] ) );
    this->dynamBar.setFillColor( this->db_color );
    this->dynamBar.setOutlineThickness( this->db_outl_thick );
    this->dynamBar.setOutlineColor( this->db_outl_color );


    sf::FloatRect tmpFloatRect = fullBar.getGlobalBounds();
    sf::Vector2f fullBarPos = tmpFloatRect.getPosition();
    sf::Vector2f fullBarSize = tmpFloatRect.getSize();


    /* 
    Create the string which indicates the name of the content as well as 
    the current HP and max HP.
    */
    std::ostringstream streamObj, streamObj2;
    // Set fixed and precision to 2
    streamObj << std::fixed << std::setprecision(2) << this->HPnum[1];
    string currHP = streamObj.str();
    streamObj2 << std::fixed << std::setprecision(2) << this->HPnum[0];
    string maxHP = streamObj2.str();
    string tmpStr = contName + ": " + currHP + " / " + maxHP;

    // Update the info box.
    this->infoBox.setPos( fb_p_d[0], 
        fb_p_d[1] + fb_p_d[3] + fb_outl_thick );
    this->infoBox.setBoxOutlThick( this->fb_outl_thick );
    this->infoBox.setBoxOutlineColor( this->fb_outl_color );
    this->infoBox.txt.setString( tmpStr );
    this->infoBox.update();

}

void SFML_HPBar_XYQ::beDrawn( sf::RenderWindow& window ) const{

    if( this->enabled ){

        window.draw( this->fullBar );
        window.draw( this->dynamBar );
        this->infoBox.beDrawn( window );

    }

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

float SFML_HPBar_XYQ::get_FB_width() const
    {return this->fb_p_d[2];}
void SFML_HPBar_XYQ::set_FB_width( float width_in )
    {this->fb_p_d[2] = width_in;}

float SFML_HPBar_XYQ::get_FB_height() const
    {return this->fb_p_d[3];}
void SFML_HPBar_XYQ::set_FB_height( float height_in )
    {this->fb_p_d[3] = height_in;}

float SFML_HPBar_XYQ::get_FB_x() const
    {return this->db_p_d[0];}
void SFML_HPBar_XYQ::set_FB_x( float x_in ){
    this->position.x = x_in;
    //this->fb_p_d[0] = x_in;
}

float SFML_HPBar_XYQ::get_FB_y() const
    {return this->db_p_d[1];}
void SFML_HPBar_XYQ::set_FB_y( float y_in ){
    this->position.y = y_in;
    //this->fb_p_d[1] = y_in;
}

float SFML_HPBar_XYQ::get_in_marg() const
    {return this->in_marg;}
void SFML_HPBar_XYQ::set_in_marg( float in_marg )
    {this->in_marg = in_marg;}

float SFML_HPBar_XYQ::get_FB_outl_thick() const
    {return this->fb_outl_thick;}
void SFML_HPBar_XYQ::set_FB_outl_thick( float db_outl_thick )
    {this->db_outl_thick = db_outl_thick;}

float SFML_HPBar_XYQ::get_DB_outl_thick() const
    {return this->db_outl_thick;}
void SFML_HPBar_XYQ::set_DB_outl_thick( float db_outl_thick ){
    if( this->in_marg <= db_outl_thick ){
        throw std::range_error( "The dynamic bar's outline thickness cannot exceed the inner to outer bars' margin." );
    }else{
        this->db_outl_thick = db_outl_thick;
    }
}

sf::Color SFML_HPBar_XYQ::get_FB_color() const
    {return this->fb_color;}
void SFML_HPBar_XYQ::set_FB_color( sf::Color fb_color )
    {this->fb_color = fb_color;}

sf::Color SFML_HPBar_XYQ::get_DB_color() const
    {return this->db_color;}
void SFML_HPBar_XYQ::set_DB_color( sf::Color db_color )
    {this->db_color = db_color;}

sf::Color SFML_HPBar_XYQ::get_FB_outl_color() const
    {return this->fb_outl_color;}
void SFML_HPBar_XYQ::set_FB_outl_color( sf::Color fb_outl_color )
    {this->fb_outl_color = fb_outl_color;}

sf::Color SFML_HPBar_XYQ::get_DB_outl_color() const
    {return this->db_outl_color;}
void SFML_HPBar_XYQ::set_DB_outl_color( sf::Color db_outl_color )
    {this->db_outl_color = db_outl_color;}

float SFML_HPBar_XYQ::getHP() const
    { return this->HPnum[1]; }
void SFML_HPBar_XYQ::setHP( float HP_num ){ 
    if( HP_num <= HPnum[0] ){
        this->HPnum[1] = HP_num; 
    }else{
        throw std::range_error( "Given HP amount surpasses maximum HP." );
        return;
    }
}

float SFML_HPBar_XYQ::getMaxHP() const
    {return this->HPnum[0];}
void SFML_HPBar_XYQ::setMaxHP( float maxHP ){
    
    if( maxHP <= 0 ){
        throw std::runtime_error( "Max HP cannot be zero or negative." );
        return;
    }

    float HP_perc = HPnum[1]/HPnum[0];

    this->HPnum[0] = maxHP;
    this->HPnum[1] = maxHP*HP_perc;

}


// ====================================================================== <<<<<


