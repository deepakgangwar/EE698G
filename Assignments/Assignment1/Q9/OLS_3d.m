function [ theta ] = OLS_3d( points )
%OLS_3d Least square plane fit

point_count = size(points);%plane eq z=ax+by+c
A = [points(:,1),points(:,2),ones(point_count(1),1)];
Z = points(:,3);
theta = ((A'*A)^-1)*A'*Z;
end
