
#include "quadcopter.h"

int main(void){

  Attitude attitude;

  while(1){
    update_control_variables(&attitude.roll);
    update_control_variables(&attitude.pitch);
    update_control_variables(&attitude.yaw);
  }
}
