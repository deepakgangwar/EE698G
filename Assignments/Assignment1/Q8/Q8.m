clear;
clc;
load('data_points_line.mat');

%% Q8 parameters
S = 2;
RANSAC_threshold = 3;
required_probability = 0.99;
outlier_percentage = 10;
inlier_fraction = (100 - outlier_percentage)/100;

figure('name','Question 8','units','normalized','outerposition',[0 0 1 1])
subplot(1,2,1);
plot(points(:,1),points(:,2),'.b');
hold on;

%% least square fit of all points
line_whole = OLS(points);%line = [slope ;C]
x = min(points(:,1)):0.5:max(points(:,1));
plot(x,line_whole(1)*x+line_whole(2),'-r');
hold on;

%% RANSAC then least square fit
inliers = Ransac(points,required_probability,inlier_fraction,S,RANSAC_threshold);
line_inliers = OLS(inliers);
plot(x,line_inliers(1)*x+line_inliers(2),'-g');
%% Graph Labels and titles
legend({'points','Least Square using all points','Least Square using inliers'},'location','northwest');
xlabel('X');
ylabel('Y');
title('(Q8a) Least Square and RANSAC');
hold off;

subplot(1,2,2);
plot(points(:,1),points(:,2),'.b');
hold on;

%% PCA of all points
PCA_whole = PCA(points);
plot(x,PCA_whole(1)*x+PCA_whole(2),'-r');
hold on;

%% RANSAC then PCA
PCA_inliers = PCA(inliers);
plot(x,PCA_inliers(1)*x+PCA_inliers(2),'-g');
%% Graph Labels and titles
legend({'points','PCA using all points','PCA using inliers'},'location','northwest');
xlabel('X');
ylabel('Y');
title('(Q8b) PCA and RANSAC');
hold off;