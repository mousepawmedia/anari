#include "anari/layerinstance.hpp"
using std::string;
using std::list;
using std::cout;
using std::endl;

//Constructor
LayerInstance::LayerInstance(Layer* newLayer, Matrix newMatrix):
    zPreference(-1)
{
    layer = newLayer;
    matrix = newMatrix;
    maxPart[0] = -1;
    maxPart[1] = -1;
    minPart[0] = -1;
    minPart[1] = -1;
    //Will modify this when we figure out the matrices
}

//Destructor
LayerInstance::~LayerInstance()
{
    //dtor
}

//Sets and gets
void LayerInstance::setMatrix(Matrix newMatrix)
{
    matrix = newMatrix;
    /*In the future, the matrix will affect the LayerInstance's location on the
    *canvas, so we will want to update its Frame accordingly.*/
    update(zPreference);
}


void LayerInstance::setLayer(Layer* newLayer)
{
    layer = newLayer;
}

Layer* LayerInstance::getLayer()
{
    return layer;
}


Matrix LayerInstance::getMatrix()
{
    return matrix;
}


void LayerInstance::setZPreference(int newPref)
{
    zPreference = newPref;
}


int LayerInstance::getZPreference()
{
    return zPreference;
}

void LayerInstance::setXMaxPart(int newX)
{
    maxPart[0] = newX;
}

///Set Y Max Partition
void LayerInstance::setYMaxPart(int newY)
{
    maxPart[1] = newY;
}

///Set X Min Partition
void LayerInstance::setXMinPart(int newX)
{
    minPart[0] = newX;
}

///Set Y Min Partition
void LayerInstance::setYMinPart(int newY)
{
    minPart[1] = newY;
}

///Get X Max Partition
int LayerInstance::getXMaxPart()
{
    return maxPart[0];
}

///Get Y Max Partition
int LayerInstance::getYMaxPart()
{
    return maxPart[1];
}

///Get X Min Partition
int LayerInstance::getXMinPart()
{
    return minPart[0];
}

///Get Y Min Partition
int LayerInstance::getYMinPart()
{
    return minPart[1];
}

/*This method returns the x coordinate of the LayerInstance's center/origin
*point. The coordinates of the LayerInstance can possibly be different from
*the origin coordinates of the base Layer that it's pointing to, because the
*transformation matrix may move that specific LayerInstance to a different
*position on the screen.*/
int LayerInstance::getOriginX()
{
    /*TODO:Multiply base Layer's origin coordinates by this LayerInstance's
    *transformation matrix.*/
    return layer->getOriginX();
}
//Get the y coordinate of the LayerInstance's center point
int LayerInstance::getOriginY()
{
    //TODO:Insert Matrix math here
    return layer->getOriginY();
}

//Render method that displays the LayerInstance to the screen.
void LayerInstance::render()
{
    //LayerInstance will not render if it's not visible
    if(layer->isVisible())
    {
        /*Tells its Layer pointer to render (passing in the matrix as a
        *parameter.)*/
        (*layer).render(matrix);
    }
}

//Observable methods
void LayerInstance::addObserver(Observer* newObs)
{
    //Will try to to find a better way to add/remove observers
    bool alreadySubscribed = false;
    //Loop through Observers, make sure that the Observer isn't already in list
    for(list<Observer*>::iterator it = observers.begin();
    it != observers.end(); ++it)
    {
        if((*it) == newObs)
        {
            //The Observer was already in the list
            std::cout << "Item already found in LayerInstances observers" <<
            std::endl;
            alreadySubscribed = true;
        }
    }
    //If the Observer wasn't in the list, add it at the end.
    if(!alreadySubscribed)
    {
        observers.push_back(newObs);
    }
}

//This method removes an Observer from the Observer list
void LayerInstance::removeObserver(Observer* newObs)
{
    //Loop through Observer looking for the value we want to delete
    for(list<Observer*>::iterator it = observers.begin();
    it != observers.end(); ++it)
    {
        if((*it) == newObs)
        {
            //Delete current value
            observers.erase(it);
            return;
        }
    }
}

//This method updates all of the LayerInstance's subscribers.
void LayerInstance::update()
{
    //Loop through Observer list
    for(list<Observer*>::const_iterator it = observers.begin();
    it != observers.end(); ++it)
    {
        //Call the update method for each Observer
        (*it)->update(zPreference);
    }
}

/*This method is overidden from Observer class. It's called by the
*LayerInstance's Layer pointer on dimension/property change. It does
*the same thing as the function above*/
void LayerInstance::update(int zPref)
{
    (void)zPref;
    //Loop through the LayerInstance's Observers
    for(list<Observer*>::const_iterator it = observers.begin();
    it != observers.end(); ++it)
    {
        //Update the current Observer object
        (*it)->update(zPreference);
    }
}

//Method that returns the number of Observers subscribed to the object
unsigned int LayerInstance::getNumOfObservers()
{
    return observers.size();
}


/*Method that copies the contents of one LayerInstance to another. It's
*not currently in use.*/
void LayerInstance::copyContentsFrom(LayerInstance that)
{
    zPreference = that.zPreference;
    layer = that.layer;
    maxPart[0] = that.maxPart[0];
    maxPart[1] = that.maxPart[1];
    minPart[0] = that.minPart[0];
    minPart[1] = that.minPart[1];
    observers = that.observers;
    matrix = that.matrix;
}