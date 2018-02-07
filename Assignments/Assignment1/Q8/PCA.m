function [theta] = PCA( points )
%PCA computes line of principal component

mean_x = mean(points(:,1));
mean_y = mean(points(:,2));
x = points(:,1) - mean_x;
y = points(:,2) - mean_y;
covariance = cov(x,y);
[eig_vector,eig_value] = eig(covariance);
if eig_value(1,1) >= eig_value(2,2)
    m = eig_vector(2,1)/eig_vector(1,1);
else
    m = eig_vector(2,2)/eig_vector(1,2);
end
c = mean_y - m * mean_x;
theta = [m;c];
end