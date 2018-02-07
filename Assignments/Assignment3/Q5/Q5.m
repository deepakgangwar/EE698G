%% Q5 Assignment 3
clc;
close all;
clear;
load('data_epipolar.mat');
figure,imshow(s.Image1);
hold on;
scatter(s.pointOfInterest(1),s.pointOfInterest(2),'*r');

%%transformations
H_hc1 = Pose_to_rot(s.X_hc1);
H_hc2 = Pose_to_rot(s.X_hc2);
H = H_hc2  \ H_hc1;

R = H(1:3,1:3);
T = H(1:3,4);

S = [0,-T(3),T(2);
	 T(3),0,-T(1);
	 -T(2),T(1),0];

E = S * R;
F = inv(s.K2')*E*inv(s.K1);
L = F * s.pointOfInterest;

for i = 1:size(s.Image1,2)
	for j = 1:size(s.Image1,1)
		if(abs([i,j,1] * L) <= 0.0002)
			s.Image2(j,i,1) = 255;
			s.Image2(j,i,2) = 0;
			s.Image2(j,i,3) = 0;
		end
	end
end

figure,imshow(s.Image2);
hold on;