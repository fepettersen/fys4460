% exwalk.m

lx = 64*4;
ly = 64*4;
p = 0.585;
ncount = 0;
perc = [];

while (size(perc,1)==0)
   ncount = ncount + 1;
   if ncount >1000
       return
   end
   z = rand(lx,ly)<p;
   [lw,num] = bwlabel(z,4);
   perc_x = intersect(lw(1,:),lw(lx,:));
   perc_y = intersect(lw(:,1),lw(:,ly));
   perc = perc_x(perc_x ~= 0);
end
% s = regionprops(lw,'Area');
% clustersize = cat(1,s.Area);
% maxarea = max(clustersize);
% i = find(clustersize == maxarea);
zz = lw==perc(1);

%zz now contains the spanning cluster
imagesc(zz); %visualize spanning cluster

%Run walk on this cluster

[l,r] = walk(zz);
zzz = l.*r; % Find points where both l and r anre nonzero
zadd = zz + zzz;
subplot(2,2,1), imagesc(zz);
subplot(2,2,2), imagesc(zadd);
subplot(2,2,3), imagesc(zzz);
subplot(2,2,4), imagesc(1+r>0);
figure(4)
imagesc(l)
title('left')
figure(5)
imagesc(r)
title('right')