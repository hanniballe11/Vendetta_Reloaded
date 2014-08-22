/*
 * Effect.cpp
 *
 *  Created on: 6 juil. 2012
 *      Author: Erwann
 */

#include "Effect.hpp"

Effect::Effect()
{
    current_state=0;
    nb_anim=0;
    nb_state=0;
    random_anim=0;
    is_active=false;
    counter=0;
}
Effect::Effect(const sf::Texture &Img, unsigned int anims, unsigned int states, const sf::Vector2f &Position) : Entity(Img, Position)
{
    current_state=0;
    nb_anim=anims;
    nb_state=states;
    random_anim=rand() % nb_anim;
    setTextureRect(sf::IntRect(getTexture()->getSize().x/nb_anim*random_anim,getTexture()->getSize().y/nb_state*current_state, getTexture()->getSize().x/nb_anim, getTexture()->getSize().y/nb_state));
    current_state++;
    is_active=true;
    counter=0;
}
Effect::~Effect()
{

}
void Effect::update()
{
    if(counter==COUNTERMAX)
    {
        if(current_state<nb_state)
        {
            setTextureRect(sf::IntRect(getTexture()->getSize().x/nb_anim*random_anim,getTexture()->getSize().y/nb_state*current_state, getTexture()->getSize().x/nb_anim, getTexture()->getSize().y/nb_state));
            current_state++;
            is_active=true;
        }
        else
        {
            is_active=false;
        }
        counter=0;
    }
    counter++;
}
unsigned int Effect::getState()
{
    return current_state;
}
void Effect::setTexture(sf::Texture &Img)
{
    Entity::setTexture(Img);
    setTextureRect(sf::IntRect(0,0, getTexture()->getSize().x, Img.getSize().y/4));
}
bool Effect::getActive()
{
    return is_active;
}
void Effect::activate()
{
    is_active=true;
}
void Effect::draw(sf::RenderTarget* sys)
{
    if(is_active && sys!=0)
    {
        sys->draw(*this);
    }
}
