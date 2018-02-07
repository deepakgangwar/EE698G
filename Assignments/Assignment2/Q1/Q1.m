clc;
clear;
load('Problem.mat');
gnd_threshold = -2;
j = 1;
for i = 1:size(Problem.scan)
	if Problem.scan(i,3) > gnd_threshold
		scan_without_gnd(j,:) = Problem.scan(i,:);
		j = j+1;
	end
end
H_hl = Pose_to_rot(Problem.X_hl);

for i = 1:5
	H_hc = Pose_to_rot(Problem.X_hc(i).X_hc);
	H_cl = H_hc \ H_hl;
	j = 1; 
	for k = 1:size(scan_without_gnd)
		temp = H_cl * [scan_without_gnd(k,:),1]';
		if temp(3,1) >= 0
			points_img(j,:) = [Problem.K(i).K,zeros(3,1)] * temp;
			points_img(j,:) = points_img(j,:)/points_img(j,3);
% 			if points_img(j,:) > 0
% 				Problem.Image(i).I(ceil(points_img(j,2)),ceil(points_img(j,1)),:) = 0;
% 			end
			j = j + 1;
		end
	end
	figure, imshow(Problem.Image(i).I);
	hold on;
    pause(0.1);
	scatter(points_img(:,1),points_img(:,2),0.5);
 	hold off;
end