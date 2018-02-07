function [x,P]= UKF_update(x,P,z,R,idf,lm)
% correcting the predicted pose using Kalman gain.

% Inputs:
%   x, P -  state and covariance
%   z, R - range-bearing measurements and covariances
%   idf - indecies of each landmark from which measurements have arrived 
 
% Outputs:
%   x, P - updated state and covariance


% <---------------------------- TO DO -------------------------->
 
n = size(x,1);
lambda = 1;alpha = 0.125;beta = 2;
% alpha = 0.001;beta = 2;kappa = 0;
% lambda=(alpha^2*(n+kappa))-n;

sigma_points = zeros(n,2*n+1);
weight_mean = zeros(1,2*n+1);
weight_covariance = zeros(1,2*n+1);


size_idf = size(idf);
if numel(idf) == 0
	return;
else
	for j=1:size_idf

		z_predict = zeros(size(z,1),1);
		Pxz = zeros(n,size(z,1));
		S = zeros(size(z,1),size(z,1));
		Z = zeros(size(z,1),n);
		diff = sqrtm((n+lambda)*P);

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
			l = lm(:,idf(j));
			z(2,j) = pi_to_pi(z(2,j));
			dist = sqrt((sigma_points(1,i)-l(1))^2+(sigma_points(2,i)-l(2))^2);
			Z(:,i) = [dist;	pi_to_pi(atan2(l(2)-sigma_points(2,i),l(1)-sigma_points(1,i)) - sigma_points(3,i))];

			z_predict = z_predict + weight_mean(i)*Z(:,i);
		end
		% z_predict(2) = pi_to_pi(z_predict(2));
		for i = 1:2*n +1
			Pxz = Pxz + weight_covariance(i) * ((sigma_points(:,i) - x) * (Z(:,i) - z_predict)');
			S = S + weight_covariance(i) * (Z(:,i) - z_predict) * (Z(:,i) - z_predict)';
		end 
		S = S + R;
		K = Pxz * pinv(S);
		z(2,j) = pi_to_pi(z(2,j));
		x = x + K * (z(:,j) - z_predict);
		x(3) = pi_to_pi(x(3));
		P = P - K * S * K';
	end
end



end      

     
    
    
  

         