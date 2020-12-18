#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "unitree_legged_sdk/unitree_legged_sdk.h"
#include <math.h>
#include <iostream>
#include <string.h>

#include "simple_udp.h"
//simple_udp udp0("192.168.1.233",5555);// usbイーサネット
//simple_udp udp0("192.168.123.161",5555);// 内部イーサネット
//simple_udp udp0("192.168.1.244",5555);// wifi dongle
simple_udp udp0("0.0.0.0",5555);// all ip adress

using namespace UNITREE_LEGGED_SDK;
using namespace std;

const long TIMEOUT = 300;//この時間以上信号が送られない場合動作を停止する(ms)

#include <sys/time.h>
#include <cstdio>
long getCurrentTime() {
      struct timeval tv;
      gettimeofday(&tv,NULL);
      return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

class Custom
{
public:
    Custom(uint8_t level): safe(LeggedType::A1), udp(level){
        udp.InitCmdData(cmd);
    }
    void UDPRecv();
    void UDPSend();
    void forward();
    void backward();
    void left();
    void right();
    void clockwise();
    void counterclockwise();
    void stand();
    void face_up();
    void face_down();
    void down();

    Safety safe;
    UDP udp;
    HighCmd cmd = {0};
    HighState state = {0};
    int motiontime = 0;
    float dt = 0.002;     // 0.001~0.01
};

int main()
{
        int ch = 0;
        std::string rdata;
        Custom custom(HIGHLEVEL);
        InitEnvironment();
        udp0.udp_bind();


        while(ch != 'q'){
//       printf("looping\n");


//       LoopFunc loop_control_stand("control_loop_for", custom.dt,    boost::bind(&Custom::stand, &custom));
//       LoopFunc loop_udpSend_stand("udp_send_for",  custom.dt, 3, boost::bind(&Custom::UDPSend, &custom));
//       LoopFunc loop_udpRecv_stand("udp_recv_for",  custom.dt, 3, boost::bind(&Custom::UDPRecv, &custom));

//       loop_udpSend_stand.start();
//       loop_udpRecv_stand.start();
//       loop_control_stand.start();

       sleep(0.1);


        if(udp0.udp_recv(rdata))ch = rdata[0];

//  W = 87
        if(ch == 'w'){


            printf("forward %c\n", ch);
            LoopFunc loop_control_forward("control_loop_for", custom.dt,    boost::bind(&Custom::forward, &custom));
            LoopFunc loop_udpSend_forward("udp_send_for",  custom.dt, 3, boost::bind(&Custom::UDPSend, &custom));
            LoopFunc loop_udpRecv_forward("udp_recv_for",  custom.dt, 3, boost::bind(&Custom::UDPRecv, &custom));

            loop_udpSend_forward.start();
            loop_udpRecv_forward.start();
            loop_control_forward.start();

            long lasttime = getCurrentTime();

            while(ch == 'w'){
              sleep(0.002);

              if(udp0.udp_recv(rdata))lasttime = getCurrentTime();

              long timediff = getCurrentTime() - lasttime;
              //std::cout << "timediff:" << timediff << std::endl;

              if(timediff > TIMEOUT){
                cout << "timeout forward loop" << endl;
                ch = 'B';
                break;
              }

              if(ch != 'w'){
                cout << "break forward loop" << endl;
                break;
              }
            }
        }


//  S = 83
       else if(ch == 's'){
            printf("backward %c\n", ch);
            LoopFunc loop_control_backward("control_loop_for", custom.dt,    boost::bind(&Custom::backward, &custom));
            LoopFunc loop_udpSend_backward("udp_send_for",  custom.dt, 3, boost::bind(&Custom::UDPSend, &custom));
            LoopFunc loop_udpRecv_backward("udp_recv_for",  custom.dt, 3, boost::bind(&Custom::UDPRecv, &custom));

            loop_udpSend_backward.start();
            loop_udpRecv_backward.start();
            loop_control_backward.start();

            long lasttime = getCurrentTime();

            while(ch == 's'){
              sleep(0.002);

              if(udp0.udp_recv(rdata))lasttime = getCurrentTime();

              long timediff = getCurrentTime() - lasttime;
              //std::cout << "timediff:" << timediff << std::endl;

              if(timediff > TIMEOUT){
                cout << "timeout back loop" << endl;
                ch = 'B';
                break;
              }

              if(ch != 's'){
                cout << "break back loop" << endl;
                break;
              }
            }

        }


//  A = 65
        else if(ch == 'a'){
            printf("left %c\n", ch);
            LoopFunc loop_control_left("control_loop_for", custom.dt,    boost::bind(&Custom::left, &custom));
            LoopFunc loop_udpSend_left("udp_send_for",  custom.dt, 3, boost::bind(&Custom::UDPSend, &custom));
            LoopFunc loop_udpRecv_left("udp_recv_for",  custom.dt, 3, boost::bind(&Custom::UDPRecv, &custom));

            loop_udpSend_left.start();
            loop_udpRecv_left.start();
            loop_control_left.start();


            long lasttime = getCurrentTime();

            while(ch == 'a'){
              sleep(0.002);

              if(udp0.udp_recv(rdata))lasttime = getCurrentTime();

              long timediff = getCurrentTime() - lasttime;
              //std::cout << "timediff:" << timediff << std::endl;

              if(timediff > TIMEOUT){
                cout << "timeout left loop" << endl;
                ch = 'B';
                break;
              }

              if(ch != 'a'){
                cout << "break left loop" << endl;
                break;
              }
            }

        }



//  D = 68
        else if(ch == 'd'){
            printf("right %c\n", ch);
            LoopFunc loop_control_right("control_loop_for", custom.dt,    boost::bind(&Custom::right, &custom));
            LoopFunc loop_udpSend_right("udp_send_for",  custom.dt, 3, boost::bind(&Custom::UDPSend, &custom));
            LoopFunc loop_udpRecv_right("udp_recv_for",  custom.dt, 3, boost::bind(&Custom::UDPRecv, &custom));

            loop_udpSend_right.start();
            loop_udpRecv_right.start();
            loop_control_right.start();

            long lasttime = getCurrentTime();

            while(ch == 'd'){
              sleep(0.002);

              if(udp0.udp_recv(rdata))lasttime = getCurrentTime();

              long timediff = getCurrentTime() - lasttime;
              //std::cout << "timediff:" << timediff << std::endl;

              if(timediff > TIMEOUT){
                cout << "timeout right loop" << endl;
                ch = 'B';
                break;
              }

              if(ch != 'd'){
                cout << "break right loop" << endl;
                break;
              }
            }

        }


//  X = 88
        else if(ch == 'x'){
            printf("clockwise %c\n", ch);
            LoopFunc loop_control_clockwise("control_loop_for", custom.dt,    boost::bind(&Custom::clockwise, &custom));
            LoopFunc loop_udpSend_clockwise("udp_send_for",  custom.dt, 3, boost::bind(&Custom::UDPSend, &custom));
            LoopFunc loop_udpRecv_clockwise("udp_recv_for",  custom.dt, 3, boost::bind(&Custom::UDPRecv, &custom));

            loop_udpSend_clockwise.start();
            loop_udpRecv_clockwise.start();
            loop_control_clockwise.start();

            long lasttime = getCurrentTime();

            while(ch == 'x'){
              sleep(0.002);

              if(udp0.udp_recv(rdata))lasttime = getCurrentTime();

              long timediff = getCurrentTime() - lasttime;
              //std::cout << "timediff:" << timediff << std::endl;

              if(timediff > TIMEOUT){
                cout << "timeout clockwise loop" << endl;
                ch = 'B';
                break;
              }

              if(ch != 'x'){
                cout << "break clockwise loop" << endl;
                break;
              }
            }

        }



//  C = 67
        else if(ch == 'c'){
            printf("counterclockwise %c\n", ch);
            LoopFunc loop_control_counterclockwise("control_loop_for", custom.dt,    boost::bind(&Custom::counterclockwise, &custom));
            LoopFunc loop_udpSend_counterclockwise("udp_send_for",  custom.dt, 3, boost::bind(&Custom::UDPSend, &custom));
            LoopFunc loop_udpRecv_counterclockwise("udp_recv_for",  custom.dt, 3, boost::bind(&Custom::UDPRecv, &custom));

            loop_udpSend_counterclockwise.start();
            loop_udpRecv_counterclockwise.start();
            loop_control_counterclockwise.start();

            long lasttime = getCurrentTime();

            while(ch == 'c'){
              sleep(0.002);

              if(udp0.udp_recv(rdata))lasttime = getCurrentTime();

              long timediff = getCurrentTime() - lasttime;
              //std::cout << "timediff:" << timediff << std::endl;

              if(timediff > TIMEOUT){
                cout << "timeout counterclockwise loop" << endl;
                ch = 'B';
                break;
              }

              if(ch != 'c'){
                cout << "break stand loop" << endl;
                break;
              }
           }
        }

        else if(ch == 'i'){
            printf("face up %c\n", ch);
            LoopFunc loop_control_face_up("control_loop_for", custom.dt,    boost::bind(&Custom::face_up, &custom));
            LoopFunc loop_udpSend_face_up("udp_send_for",  custom.dt, 3, boost::bind(&Custom::UDPSend, &custom));
            LoopFunc loop_udpRecv_face_up("udp_recv_for",  custom.dt, 3, boost::bind(&Custom::UDPRecv, &custom));

            loop_udpSend_face_up.start();
            loop_udpRecv_face_up.start();
            loop_control_face_up.start();

            while(ch == 'i'){
              sleep(0.002);
              if(udp0.udp_recv(rdata))ch = rdata[0];
           }
        }

        else if(ch == 'k'){
            printf("face down %c\n", ch);
            LoopFunc loop_control_face_down("control_loop_for", custom.dt,    boost::bind(&Custom::face_down, &custom));
            LoopFunc loop_udpSend_face_down("udp_send_for",  custom.dt, 3, boost::bind(&Custom::UDPSend, &custom));
            LoopFunc loop_udpRecv_face_down("udp_recv_for",  custom.dt, 3, boost::bind(&Custom::UDPRecv, &custom));

            loop_udpSend_face_down.start();
            loop_udpRecv_face_down.start();
            loop_control_face_down.start();

            while(ch == 'k'){
              sleep(0.002);
              if(udp0.udp_recv(rdata))ch = rdata[0];
           }
        }

        else if(ch == 'n'){
            printf("down %c\n", ch);
            LoopFunc loop_control_down("control_loop_for", custom.dt,    boost::bind(&Custom::down, &custom));
            LoopFunc loop_udpSend_down("udp_send_for",  custom.dt, 3, boost::bind(&Custom::UDPSend, &custom));
            LoopFunc loop_udpRecv_down("udp_recv_for",  custom.dt, 3, boost::bind(&Custom::UDPRecv, &custom));

            loop_udpSend_down.start();
            loop_udpRecv_down.start();
            loop_control_down.start();

            while(ch == 'n'){
              sleep(0.002);
              if(udp0.udp_recv(rdata))ch = rdata[0];
           }
        }


     }
     exit(0);
    return 0;
}

void Custom::UDPRecv()
{
    udp.Recv();
}

void Custom::UDPSend()
{
    udp.Send();
}


void Custom::forward()
{
    udp.GetRecv(state);
    cmd.sideSpeed = 0.0f;
    cmd.rotateSpeed = 0.0f;
    cmd.mode = 2;
    cmd.forwardSpeed = 0.2f;
    //cmd.forwardSpeed = 0.5f;
    cmd.roll = 0;
    cmd.pitch = 0;
    cmd.yaw = 0;
    udp.SetSend(cmd);

}


void Custom::backward()
{
    udp.GetRecv(state);
    cmd.mode = 2;
    cmd.forwardSpeed = -0.2f;
    cmd.sideSpeed = 0.0f;
    cmd.rotateSpeed = 0.0f;
    cmd.roll = 0;
    cmd.pitch = 0;
    cmd.yaw = 0;
    udp.SetSend(cmd);

}



void Custom::left()
{
    udp.GetRecv(state);
    cmd.mode = 2;
    cmd.sideSpeed = 0.2f;    //   side_speed
    cmd.forwardSpeed = 0.0f;
    cmd.rotateSpeed = 0.0f;
    cmd.roll = 0;
    cmd.pitch = 0;
    cmd.yaw = 0;
    udp.SetSend(cmd);
}



void Custom::right()
{
    udp.GetRecv(state);
    cmd.mode = 2;
    cmd.sideSpeed = -0.2f;    //   side_speed
    cmd.forwardSpeed = 0.0f;
    cmd.rotateSpeed = 0.0f;
    cmd.roll = 0;
    cmd.pitch = 0;
    cmd.yaw = 0;
    udp.SetSend(cmd);
}



void Custom::clockwise()
{
    udp.GetRecv(state);
    cmd.mode = 2;
    cmd.forwardSpeed = 0.0f;
    cmd.sideSpeed = 0.0f;
    cmd.rotateSpeed = 0.2f;    //   rotate_speed
    cmd.roll = 0;
    cmd.pitch = 0;
    cmd.yaw = 0;
    udp.SetSend(cmd);
}

void Custom::counterclockwise()
{
    udp.GetRecv(state);
    cmd.mode = 2;
    cmd.forwardSpeed = 0.0f;
    cmd.sideSpeed = 0.0f;
    cmd.rotateSpeed = -0.2f;
    cmd.roll = 0;
    cmd.pitch = 0;
    cmd.yaw = 0;
    udp.SetSend(cmd);
}

void Custom::stand()
{
   udp.GetRecv(state);
   cmd.mode = 2;
   udp.SetSend(cmd);
}

void Custom::face_up()
{
   udp.GetRecv(state);
   cmd.forwardSpeed = 0.0f;
   cmd.sideSpeed = 0.0f;
   cmd.rotateSpeed = 0.0f;
   cmd.bodyHeight = 0.0f;

   cmd.mode = 1;      // 0:idle, default stand      1:forced stand     2:walk continuously
   cmd.roll  = 0;
   cmd.pitch = 1.0f;
   cmd.yaw = 0;
   udp.SetSend(cmd);
}

void Custom::face_down()
{
   udp.GetRecv(state);
   cmd.forwardSpeed = 0.0f;
   cmd.sideSpeed = 0.0f;
   cmd.rotateSpeed = 0.0f;
   cmd.bodyHeight = 0.0f;

   cmd.mode = 1;      // 0:idle, default stand      1:forced stand     2:walk continuously
   cmd.roll  = 0;
   cmd.pitch = -1.0f;
   cmd.yaw = 0;
   udp.SetSend(cmd);
}

void Custom::down()
{
   udp.GetRecv(state);
   cmd.forwardSpeed = 0.0f;
   cmd.sideSpeed = 0.0f;
   cmd.rotateSpeed = 0.0f;
   cmd.bodyHeight = -1.0f;

   cmd.mode = 1;      // 0:idle, default stand      1:forced stand     2:walk continuously
   cmd.roll  = 0;
   cmd.pitch = 0;
   cmd.yaw = 0;
   udp.SetSend(cmd);
}
