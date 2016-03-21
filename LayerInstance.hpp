/**
*Anari Graphics System, version 0.1
*LayerInstance Class
*This class represents one instance of a Layer object that will be
*contained in a Frame object to be sequentially rendered. It contains
*a transformation matrix variable, that describes the manipulation of
*the original Layer object's image.
*The LayerInstance class inherits from both the Observable and Observer
*classes. This is because a LayerInstance wants to know when its parent
*Layer changes properties (like dimensions), and it also wants to update
*the Frame that it's stored in, so that the Frame can update its grid
*appropriately.
*Last Updated: 17 February 2016
*
*Copyright (C) MousePaw Games
*Licensing:
*/

#ifndef LAYERINSTANCE_H
#define LAYERINSTANCE_H

#include "Layer.hpp"
#include "Observable.hpp"


//NOTE: Temp typedef to represent matrix
typedef int Matrix;

class LayerInstance : public Observable, public Observer
{
    public:
        /**Constructor with optional Layer* and Matrix parameters
        *\param a Layer* that the new LayerInstance will point to.
        *\param a Matrix that the new LayerInstance will implement as a
        *   transformation matrix*/
        LayerInstance(Layer* newLayer=nullptr, Matrix newMatrix=-1);

         ///Destructor
        virtual ~LayerInstance();

        //Sets and Gets
        ///Set Matrix
        void setMatrix(Matrix newMatrix);
        ///Set Layer
        void setLayer(Layer* newLayer);
        ///Get Matrix
        Matrix getMatrix();
        ///Get Layer
        Layer* getLayer();

        ///Set ZPreference
        void setZPreference(int newPref);

        ///Get ZPreference
        int getZPreference();

        //Sets and Gets for min/max partition coordinates
        ///Set X Max Partition
        void setXMaxPart(int newX);

        ///Set Y Max Partition
        void setYMaxPart(int newY);

        ///Set X Min Partition
        void setXMinPart(int newX);

        ///Set Y Min Partition
        void setYMinPart(int newY);

        ///Get X Max Partition
        int getXMaxPart();

        ///Get Y Max Partition
        int getYMaxPart();

        ///Get X Min Partition
        int getXMinPart();

        ///Set Y Min Partition
        int getYMinPart();

        ///Get the x coordinate of the LayerInstance's center point
        int getOriginX();
        ///Get the y coordinate of the LayerInstance's center point
        int getOriginY();


        /**The render method calls the render method of Layer* that the
        *LayerInstance points to, and passes the LayerInstance's transformation
        *matrix as a parameter.*/
        void render();

        //Overidden methods from Observer pattern
        void addObserver(Observer* newObs);
        void removeObserver(Observer* newObs);
        void update();
        int getNumOfObservers();

        //Overidden method from Observable interface
        void update(int zPref);

        /**Method used to copy the attributes from one LayerInstance to another
        *\param the LayerInstance whose contents will be copied into the
        *   current LayerInstance.*/
        //NOTE: Functions properly, but isn't used in the code
        void copyContentsFrom(LayerInstance that);

        /**Method that adds the current LayerInstance as a subscriber to its
         parent Layer*/
        /*NOTE: This method is no longer used in the code. When the Layer
        *creates a new LayerInstance, the LayerInstance is added as a
        *subscriber then and there, rendering this method obsolete.*/
        void subscribeToLayer();

    protected:
    private:
        ///Variable representing the "parent" Layer
        Layer* layer;

        ///The transformation matrix used for rendering
        Matrix matrix;

        ///This int represents the LayerInstance's "depth" in the Frame.
        int zPreference;

        /**These arrays represent the coordinates of the grid partitions
        *where the LayerInstance appears, the minPart coordinates represent
        *the location of the top left corner, and the maxPart coordinates
        *represent the bottom right corner.*/
        int maxPart[2];
        int minPart[2];

        /**The list of Observers (There will typically only be one Frame
        *that subscribes to a given LayerInstance)*/
        std::list<Observer*> observers;
};

#endif // LAYERINSTANCE_H