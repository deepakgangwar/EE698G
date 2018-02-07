function [theta1,theta2] = PCA( points , covariance)
%PCA computes line of principal component

 mean_x = mean(points(:,1));
 mean_y = mean(points(:,2));
% x = points(:,1) - mean_x;
% y = points(:,2) - mean_y;
% covariance = cov(x,y);
[eig_vector,eig_value] = eig(covariance);
if eig_value(1,1) >= eig_value(2,2)
    m1 = eig_vector(2,1)/eig_vector(1,1);
    m2 = eig_vector(2,2)/eig_vector(1,2);
else
    m1 = eig_vector(2,2)/eig_vector(1,2);
    m2 = eig_vector(2,1)/eig_vector(1,1);
end
c1 = mean_y - m1 * mean_x;
theta1 = [m1;c1];
c2 = mean_y - m2 * mean_x;
theta2 = [m2;c2];
end