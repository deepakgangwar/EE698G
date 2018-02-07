% function [P Q] = correspondance(temp_scan,scan1,max_tresh)
% 	temp_scan = temp_scan(1:2,:);
% 	scan1 = scan1(1:2,:);
% 	P = [];
% 	Q = [];
% 	% figure;
% 	% hold on;
% 	% scatter(scan1(1,:),scan1(2,:),'g','.');
% 	% scatter(temp_scan(1,:),temp_scan(2,:),'r','.');
	
% 	for i = 1:size(scan1(1,:)')
% 		dist = scan1 - repmat(temp_scan(:,i),[1,size(temp_scan(1,:)')]);
% 		dist = dist(1,:).^2 + dist(2,:).^2;
% 		dist = dist.^0.5;
% 		[value,index] = min(dist);
% 		if value <= max_tresh
% 			P = [P;temp_scan(:,i)'];
% 			Q = [Q;scan1(:,index)'];
% 			% line([temp_scan(1,i);scan1(1,index)],[temp_scan(2,i);scan1(2,index)]);
% 			scan1(:,index) = [Inf;Inf];
% 		end
% 	end
% 	size(P)
% end




function [P Q] = correspondance(temp_scan,scan1,max_tresh)
	temp_scan = temp_scan(1:2,:);
	scan1 = scan1(1:2,:);
	P = [];
	Q = [];
	% figure;
	% hold on;
	% scatter(scan1(1,:),scan1(2,:),'g','.');
	% scatter(temp_scan(1,:),temp_scan(2,:),'r','.');
	
	for i = 1:size(scan1(1,:)')
		dist = temp_scan - repmat(scan1(:,i),[1,size(scan1(1,:)')]);
		dist = dist(1,:).^2 + dist(2,:).^2;
		dist = dist.^0.5;
		[value,index] = min(dist);
		if value <= max_tresh
			P = [P;scan1(:,i)'];
			Q = [Q;temp_scan(:,index)'];
			% line([temp_scan(1,i);scan1(1,index)],[temp_scan(2,i);scan1(2,index)]);
			temp_scan(:,index) = [Inf;Inf];
		end
	end
	size(P)
end