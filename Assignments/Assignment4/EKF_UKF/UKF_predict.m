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
x_augmented = [x;0;0];
P_augmented = [P,zeros(n,size(Q,1));zeros(size(Q,1),n),Q];

n_augmented = size(x_augmented,1);
alpha = 0.001;beta = 2;kappa = 0;
lambda=(alpha^2*(n_augmented+kappa))-n_augmented;

sigma_points = zeros(n_augmented,2*n_augmented+1);
weight_mean = zeros(1,2*n_augmented+1);
weight_covariance = zeros(1,2*n_augmented+1);

diff = real(sqrtm((n_augmented+lambda).*P_augmented));
x_predict = zeros(n_augmented,1);
P_predict = zeros(n_augmented,n_augmented);

for i=1:(2*n_augmented + 1)
	if i == (n_augmented + 1)
		sigma_points(:,i) = x_augmented;
		weight_mean(i) = lambda/(n_augmented + lambda);
		weight_covariance(i) = weight_mean(i) + (1 - alpha^2 + beta);
	elseif i < (n_augmented + 1)
		sigma_points(:,i) = x_augmented + diff(:,i);
		weight_covariance(i) = 1/(2*(n_augmented + lambda));
		weight_mean(i) = 1/(2*(n_augmented + lambda));
	else
		sigma_points(:,i) = x_augmented - diff(:,i-n_augmented-1);
		weight_covariance(i) = 1/(2*(n_augmented + lambda));
		weight_mean(i) = 1/(2*(n_augmented + lambda));
	end
	sigma_points(3,i) = pi_to_pi(sigma_points(3,i));
 	sigma_points(1:3,i) = vehicle_model(sigma_points(1:3,i),v+sigma_points(4,i),g+sigma_points(5,i),dt);
 	sigma_points(3,i) = pi_to_pi(sigma_points(3,i));

 	x_predict = x_predict + weight_mean(i)*sigma_points(:,i);
 	x_predict(3) = pi_to_pi(x_predict(3));
end


for i = 1:2*n_augmented +1
	temp = sigma_points(:,i) - x_augmented;
	temp(3) = pi_to_pi(temp(3));
	P_predict = P_predict + weight_covariance(i) * temp * temp';
end 

x = x_predict(1:3);
x(3) = pi_to_pi(x(3));
P = P_predict(1:3,1:3);
 
end
 
