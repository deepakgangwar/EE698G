function [x,P]= UKF_predict(x,P,v,g,Q,dt)
% Inputs:
%   x, P - state and covariance
%   v, g - control inputs: velocity and gamma (steer angle)
%   Q - covariance matrix for velocity and gamma
%   dt - timestep
%
% Outputs: 
%   x, P - predicted state and covariance
 
% <------------------------- TO DO -------------------------->

n = size(x,1);
lambda = 1;alpha = 0.125;beta = 2;

sigma_points = zeros(n,2*n+1);
weight_mean = zeros(1,2*n+1);
weight_covariance = zeros(1,2*n+1);
diff = sqrt(n+lambda)*chol(P);
x_predict = zeros(n,1);
P_predict = zeros(n,n);
for i=1:2*n+1
	if i == n+1
		sigma_points(:,i) = x;
		weight_mean(i) = lambda/(n + lambda);
		weight_covariance(i) = weight_mean(i) + (1 - alpha^2 + beta);
	elseif i < n+1
		sigma_points(:,i) = x + diff(:,i);
		weight_covariance(i) = 1/(2*(n + lambda));
		weight_mean(i) = 1/(2*(n + lambda));
	else
		sigma_points(:,i) = x - diff(:,i-n-1);
		weight_covariance(i) = 1/(2*(n + lambda));
		weight_mean(i) = 1/(2*(n + lambda));
	end
	sigma_points(1,i) = sigma_points(1,i) + v * dt * cos(g + sigma_points(3,i));
 	sigma_points(2,i) = sigma_points(2,i) + v * dt * sin(g + sigma_points(3,i)); 
 	sigma_points(3,i) = pi_to_pi(sigma_points(3,i) + g);

 	x_predict = x_predict + weight_mean(i)*sigma_points(:,i);
end
% x_predict(3) = pi_to_pi(x_predict(3));
for i = 1:2*n +1
	temp = sigma_points(:,i) - x_predict;
	temp(3) = pi_to_pi(temp(3));
	P_predict = P_predict + weight_covariance(i) * temp * temp';
end 
M = [dt*cos(g + x(3)),-v*dt*sin(g + x(3));
 	  dt*sin(g + x(3)),v*dt*cos(g + x(3));
 	  0,1];
R = M * Q * M';
x = x_predict;
x(3) = pi_to_pi(x(3));
P = P_predict + R;
 
end