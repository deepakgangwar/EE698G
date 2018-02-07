%% Q6 Assignment 3
clc;
close all;
clear;
load('data_kalman.mat');

%% declaration of constants
g = -9.8;
v = 300;
dt = 0.1;
Qt = 200^2;					% measurement model noise variance
Rt = [0.1 0; 0 0.1];		% process model noise variance

%% model
% measurement model => Z(t) = X(t) + e1
% process model => X(t) = A * X(t-1) + B * u

A = [1 dt; 0 1];
B = [0.5*dt^2; dt];
C = [1 0];
u = g;

%% plotting of part b
point_count = size(data.z);

mu = zeros(2,point_count(1));
mu(:,1) = [0; 300];
sigma = [1 0; 0 1];

for i=2:point_count(1)
	[mu(:,i),sigma] = Kalman(A,B,C,data.z(i),u,Rt,Qt,mu(:,i-1),sigma);
end

t = 0:dt:dt*(point_count(1)-1);
model = v * t + 0.5 * g * t.^2;

figure;
plot(t,mu(1,:),'red');
hold on;
plot(t,model,'blue');
plot(t,data.orig_state(:,1),'-black');
plot(t,data.z,'.red');
legend({'Kalman Filter Output','Without measurements','Actual Trajectory','Measurements'},'location','southeast');
xlabel('Height(m)');
ylabel('Time(0.1s)');
title('Part b: Position');
hold off;


%% plotting of part c
K_norm = zeros(1,point_count(1));

Rt_norm = zeros(1,point_count(1));
Rt = [data.orig_state(1,2)^2 * 10^-5 , 0; 0 , data.orig_state(1,2)^2 * 10^-5];
Rt_norm(1) = norm(Rt);

for i=2:point_count(1)
	Rt = [data.orig_state(i,2)^2 * 10^-5 , 0; 0 , data.orig_state(i,2)^2 * 10^-5];
	Rt_norm(i) = norm(Rt);
	[mu(:,i),sigma,K] = Kalman(A,B,C,data.z(i),u,Rt,Qt,mu(:,i-1),sigma);
	K_norm(i) = norm(K);
end

figure;
plot(Rt_norm,'red');
hold on;
plot(K_norm(2:end),'blue');
legend({'Norm of Rt','Norm of Kalman Gain'},'location','northeast');
title('Part C')
hold off;