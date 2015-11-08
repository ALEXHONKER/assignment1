%%source code for question 4
clear all
clc
while 1
q=input( 'Input row vector [xe ye ze psi theta phi], q=');
% input the RPY angles describing the end-effector's orientation
for i=1:3
m(i)=q(i+3)*pi/180;%
end
R6=[cos(m(3))*cos(m(2)) -sin(m(3))*cos(m(1))+cos(m(3))*sin(m(2))*sin(m(1)) sin(m(3))*sin(m(1))+cos(m(3))*sin(m(2))*cos(m(1));
   sin(m(3))*cos(m(2))  cos(m(3))*cos(m(1))+sin(m(3))*sin(m(2))*sin(m(1))  -cos(m(3))*sin(m(1))+sin(m(3))*sin(m(2))*cos(m(1));
   -sin(m(2)) cos(m(2))*sin(m(1)) cos(m(2))*cos(m(1));];%obtain the resulting rotation matrix that corresponding to the end-effector's orientation
pwx=q(1)-0.2*R6(1,3);
pwy=q(2)-0.2*R6(2,3);
pwz=q(3)-0.2*R6(3,3);
theta(1)=2*atan2(-pwx+sqrt(pwx^2+pwy^2-0.5^2),0.5+pwy) ;
theta(2)=atan2(pwx*cos(theta(1))+pwy*sin(theta(1)),pwz) ;
d3=sqrt((pwx*cos(theta(1))+pwy*sin(theta(1)))^2+pwz^2); 
disp('theta(1)=');disp(theta (1)*180/pi);
disp('theta(2)=');disp(theta (2)*180/pi);
disp('d3=');disp(d3);
R3=[cos(theta(1))*cos(theta(2)) -sin(theta(1)) cos(theta(1))*sin(theta(2));
    sin(theta(1))*cos(theta(2))  cos(theta(1)) sin(theta(1))*sin(theta(2));
    -sin(theta(2)) 0  cos(theta(2));];
R36=inv(R3)*R6;

if R36(1,3)== 0&&R36(2,3)== 0
    display('singularity');% if sin(theta(5)) equals zero, unique solution does not exist
else
    theta (4)=atan2(R36(2,3) ,R36(1,3) )*180/pi ;
    theta (5)=atan2(sqrt(R36(1,3)^2+R36(2,3)^2),R36(3,3))*180/pi ;
    theta (6)=atan2(R36(3,2) ,-R36(3,1) )*180/pi ;%solution for 0<theta(2)<pi
    display('For 0<theta(5)<pi,the value of the three joints are')
    disp('theta(4)=');disp(theta (4));
    disp('theta(5)=');disp(theta (5));
    disp('theta(6)=');disp(theta (6));%display the values of the three joints of the wrist
    theta (4)=atan2(-R36(2,3),-R36(1,3) )*180/pi ; 
    theta (5)=atan2(-sqrt(R36(1,3)^2+R36(2,3)^2),R36(3,3))*180/pi ;
    theta (6)=atan2(-R36(3,2) ,R36(3,1) )*180/pi ;%solution for -pi<theta(2)<0
    display('For -pi<theta(5)<0,,the value of the three joints are')
    disp('theta(4)=');disp(theta (4));
    disp('theta(5)=');disp(theta (5));
    disp('theta(6)=');disp(theta (6));%display the values of the three joints of the wrist
end 
end