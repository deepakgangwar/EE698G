clear;
clc;
load('data_points_plane.mat');

%% Q9 parameters
S = 3;
RANSAC_threshold = 2;
required_probability = 0.99;
outlier_percentage = 10;
inlier_fraction = (100 - outlier_percentage)/100;

%% Plot all the points
figure('name','Question 8','units','normalized','outerposition',[0 0 1 1]);
plot3(points(:,1),points(:,2),points(:,3),'.b');
hold on;
%% least square fit of all points
plane_whole = OLS_3d(points);%plane eq [a;b;c] z=ax+by+c
% plot the plane in red color
[x ,y] = meshgrid(min(points(:,1)):max(points(:,1)),min(points(:,2)):max(points(:,2)));
z = plane_whole(1)*x+plane_whole(2)*y+plane_whole(3);
red = zeros(size(x,1),size(x,2),3);
red(:,:,1) = 255 * ones(size(x,1),size(x,2));
surf(x,y,z,red);
hold on;

%% RANSAC then least square fit 
inliers = Ransac_3d( points,required_probability,inlier_fraction,S,RANSAC_threshold );
plane_inlier = OLS_3d(inliers);
% plot the plane in green color
z = plane_inlier(1)*x+plane_inlier(2)*y+plane_inlier(3);
green = zeros(size(x,1),size(x,2),3);
green(:,:,2) = 255 * ones(size(x,1),size(x,2));
surf(x,y,z,green);

%% Graph Labels and titles
shading interp;%interpolate the grids of plotted planes
legend({'points','Least Square using all points','Least Square using inliers'},'location','northwest');
xlabel('X');
ylabel('Y');
zlabel('Z')
title('(Q9) Least Square and RANSAC');
grid on;
hold off;
