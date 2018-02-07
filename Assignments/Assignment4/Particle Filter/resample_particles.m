 function [x,particles,p_w]= resample_particles(particles,p_w, N_eff)

 % resample particles

n = size(particles,2);
[value index] = max(p_w);
x = particles(:,index);
 % if(N_eff < 0.5 * n)
cdf = zeros(n,1);
for i=2:n
	cdf(i) = cdf(i-1) + p_w(i);
end
i = 1;
u = zeros(n,1);
u(i) = rand(1)/n;
for j = 1:n
	u(j) = u(1) + (j - 1)/n;
	while u(j) > cdf(i)
		i = i + 1;
		if i > 2 * N_eff;
			return
		end
	end
	particles(:,j) = particles(:,i);
	p_w(j) = 1/n;
  
end



 

 




 