function [x,P]= EKF_update(x,P,z,R,idf,lm)
 
% Inputs:
%   x, P -  state and covariance
%   z, R - range-bearing measurements and covariances
%   idf - feature index for each z
 
% Outputs:
%   x, P - updated state and covariance


% <---------------------------- TO DO -------------------------->
size_idf = size(idf,1);
if numel(idf) == 0
	return;
else
    i = 0;
	for i=1:size_idf
		l = lm(:,idf(i));
		z(2,i) = pi_to_pi(z(2,i));
		dist = sqrt((x(1)-l(1))^2+(x(2)-l(2))^2);
		z_predicted = [dist;	pi_to_pi(atan2(l(2)-x(2),l(1)-x(1)) - x(3))];

		H = [(x(1)-l(1))/dist, (x(2)-l(2))/dist, 0;
			 -(x(2)-l(2))/dist^2, (x(1)-l(1))/dist^2, -1];

		S = H * P * H' + R;
		K = P*H'*pinv(S);
		a = (z(:,i) - z_predicted);
		a(2) = pi_to_pi(a(2));
		x = x + K*a;
		x(3) = pi_to_pi(x(3));
		P = (eye(3) - K * H)*P;
	 
	end        
 
end        


     
    
    
  

         