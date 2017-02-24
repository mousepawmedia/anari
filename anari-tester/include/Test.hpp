/** Test [Anari Tester]
  * Version: 0.1
  *
  * Author(s): Andrew Peacock
  */

/* LICENSE
 * Copyright (C) 2017 MousePaw Media.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef tests_hpp
#define tests_hpp

#include <iostream>
#include <string>
#include <iomanip>
#include <Eigen/Dense>
#include "anari/timeline.hpp"
#include "anari/staticlayer.hpp"
#include "anari/iol.hpp"
#include "pawlib/iochannel.hpp"
#include "ConsoleUtil.hpp"

using namespace std;
using namespace pawlib;

//Matrix transformation
typedef Eigen::MatrixXf Matrix;

enum Command
{
    EXIT_MENU,
    PLAY,
    TIMELINE_INFO,
    ADD_LAYER,
    EDIT_LAYER,
    ADD_FRAME,
    EDIT_FRAME,
    DELETE_LAYER,
    DELETE_FRAME,
    FRAME_GRID_INFO,
    INSERT_INSTANCE,
    DELETE_INSTANCE
};

class Test
{

private:
    Timeline timeline;

public:

    //timeline
    void displayInfo();
    void editMode();
    void editMode_displayMenu();
    void editMode_editLayer();
    void editMode_addLayer();
    void editMode_addFrame();
    void editMode_deleteLayer();
    void editMode_deleteFrame();
    void editMode_displayGrid();
    void editMode_editFrame();
    void editMode_deleteLayerInstance();
    void editMode_insertLayerInstance();
    int editMode_chooseLayerType();
    void play();
    void playBackwards();

    //frame
    void frameEditMode(Frame &frame);
    void frameEditMode_displayMenu();
    void frameEditMode_setLayerInstanceMatrix(Frame &frame);
    void frameEditMode_moveLayerInstance(Frame &frame);
    void frameTest_printGridContents(Frame &frame);

    //static layer
    void staticEditMode(shared_ptr<StaticLayer> s);
    void staticEditMode_help();
    void staticEditMode_getImage(shared_ptr<StaticLayer> s);
    void staticEditMode_setImage(shared_ptr<StaticLayer> s);
    void staticEditMode_setDim(shared_ptr<StaticLayer> s);
    void staticEditMode_getDim(shared_ptr<StaticLayer> s);
    void staticEditMode_setOrigin(shared_ptr<StaticLayer> s);
    void staticEditMode_getOrigin(shared_ptr<StaticLayer> s);
    bool staticEditMode_isVisible(shared_ptr<StaticLayer> s);
    void staticEditMode_setVisibility(shared_ptr<StaticLayer> s);

    //IOL
    void iolEditMode(shared_ptr<IOL> s);
    void iolEditMode_getRepeats(shared_ptr<IOL> s);
    void iolEditMode_setRepeats(shared_ptr<IOL> s);
    void iolEditMode_getRunning(shared_ptr<IOL> s);
    void iolEditMode_setRunning(shared_ptr<IOL> s);
    void iolEditMode_getCurrentFrame(shared_ptr<IOL> s);
    void iolEditMode_setCurrentFrame(shared_ptr<IOL> s);
    void iolEditMode_isVisible(shared_ptr<IOL> s);
    void iolEditMode_setVisibility(shared_ptr<IOL> s);
    void iolEditMode_displayMenu();
};

#endif /* tests_hpp */
