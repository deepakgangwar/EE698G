function [ theta ] = OLS( points )
%OLS Least Square line fit

point_count = size(points);
A = [points(:,1),ones(point_count(1),1)];
Y = points(:,2);
theta = ((A'*A)^-1)*A'*Y;
end

