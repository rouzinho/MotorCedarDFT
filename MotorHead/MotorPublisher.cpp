/*======================================================================================================================

    Copyright 2011, 2012, 2013, 2014, 2015 Institut fuer Neuroinformatik, Ruhr-Universitaet Bochum, Germany

    This file is part of cedar.

    cedar is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    cedar is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
    License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with cedar. If not, see <http://www.gnu.org/licenses/>.

========================================================================================================================

    Institute:   Ruhr-Universitaet Bochum
                 Institut fuer Neuroinformatik

    File:        EarSubscriber.h

    Maintainer:  Tutorial Writer Person
    Email:       cedar@ini.rub.de
    Date:        2011 12 09

    Description:

    Credits:

======================================================================================================================*/

// CEDAR INCLUDES
#include "MotorPublisher.h"
#include <cedar/processing/ExternalData.h> // getInputSlot() returns ExternalData
#include <cedar/auxiliaries/MatData.h> // this is the class MatData, used internally in this step
#include "cedar/auxiliaries/math/functions.h"
#include "std_msgs/Float64.h"


// SYSTEM INCLUDES

//----------------------------------------------------------------------------------------------------------------------
// constructors and destructor
//----------------------------------------------------------------------------------------------------------------------
MotorPublisher::MotorPublisher()
:
cedar::proc::Step(true)
//mOutput(new cedar::aux::MatData(cv::Mat::zeros(50, 50, CV_32F))),
//mCenter(new cedar::aux::DoubleParameter(this,"Motor Pos",25))
{
this->declareInput("motor", true);
//this->connect(this->mCenter.get(), SIGNAL(valueChanged()), this, SLOT(reCompute()));
}
//----------------------------------------------------------------------------------------------------------------------
// methods
//----------------------------------------------------------------------------------------------------------------------
void MotorPublisher::compute(const cedar::proc::Arguments&)
{

  //subscriber for the ear. The rate of subscription is based on the one on Arduino e.g 10ms
  /*
  sub = n.subscribe("/ear", 1000, &MotorPublisher::chatterCallback,this);
  ros::Rate loop_rate(98);
  loop_rate.sleep();
  ros::spinOnce();
  */
  //change the Gaussian function with the value of the ear sensor.
  //this->mOutput->setData(cedar::aux::math::gaussMatrix(1,mGaussMatrixSizes,dat,mGaussMatrixSigmas,mGaussMatrixCenters,true));
  cedar::aux::ConstDataPtr op1 = this->getInputSlot("motor")->getData();
  cv::Mat doublepos = op1->getData<cv::Mat>();
  pub = n.advertise<std_msgs::Float64>("MotorCommand", 1000);
  ros::Rate loop_rate(98);
  float t1 = doublepos.at<float>(0);
  pos = static_cast<double> (t1);
  motorPos.data = pos;

  pub.publish(motorPos);
  loop_rate.sleep();
  ros::spinOnce();

}

void MotorPublisher::reCompute()
{
  //pos = static_cast<double>(this->mCenter->getValue());
  //mGaussMatrixCenters.clear();
  //mGaussMatrixCenters.push_back(pos);
  //this->mOutput->setData(cedar::aux::math::gaussMatrix(1,mGaussMatrixSizes,dat,mGaussMatrixSigmas,mGaussMatrixCenters,true));
}
/*
//callback for the subscriber. This one get the value of the sensor.
void MotorPublisher::chatterCallback(const std_msgs::Float64::ConstPtr& msg)
{
   ROS_INFO("I heard: [%f]", msg->data);
   dat = msg->data;
}
*/
void MotorPublisher::reset()
{

	//ros::shutdown();

}
