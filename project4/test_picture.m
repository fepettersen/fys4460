

p = linspace(0,1);
% P = zeros(length(p),length(infiles));

l = {};
hold all;
L = [200,400,600,800];
P = zeros(length(p),length(L));
Pi = zeros(length(p),length(L));

for k=1:length(L)
    wildcard = sprintf('Hubble*_%d.bmp',L(k));
    infiles =dir(wildcard);
    for j=1:length(infiles)
%         j
        infile = infiles(j).name();
        mount = imread(infile,'bmp');
        mount = im2double(mount);
        lx = length(mount);
        L2 = lx*lx;
        for i=1:length(p)
            z = mount(:,:,1)<p(i);
            [lw,num] = bwlabel(z,4);
            perc_x = intersect(lw(1,:),lw(lx,:));
            perc = perc_x(perc_x~=0);
            if isempty(perc)~=1
                P(i,k) = P(i,k)+sum(sum(lw==perc(1)))/L2;
                Pi(i,k) = Pi(i,k) +1;
            end
        end
    end
    P(:,k) = P(:,k)./length(infiles);
    Pi(:,k) = Pi(:,k)./length(infiles);
    l{k} = sprintf('L = %d',L(k));
    plot(p,P(:,k))
    drawnow
end
legend(l)

beta = log10(P(5:end,4))./log10(p(5:end)');
figure()
plot(log10(p(5:end)),beta)

figure()
hold all
for i=1:length(L)
    plot(p,Pi(:,i));
end
legend(l);
% [lw,num] = bwlabel(z,4);
% img = label2rgb(lw,'jet','k','shuffle');
% image(img)