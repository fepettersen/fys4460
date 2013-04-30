function[left,right] = walk(z);

% Left turning walker

% Returns left number of times a walker passes a site

nx = size(z,1);
ny = size(z,2);
i = find(z(1,:)>0);
iy0 = i(1);
ix0 = 1;
dirs = zeros(4,2);
dirs(1,1) = -1;
dirs(1,2) = 0;
dirs(2,1) = 0;
dirs(2,2) = -1;
dirs(3,1) = 1;
dirs(3,2) = 0;
dirs(4,1) = 0;
dirs(4,2) = 1;

nwalk = 1;
ix = ix0;
iy = iy0;
dir = 1;
left = zeros(nx,ny);

while(nwalk>0)
    left(ix,iy) = left(ix,iy) +1;
    nfound = 0;
    while(nfound==0)
        dir = dir-1;
        if dir<1
            dir = dir +4;
        end
        iix = ix + dirs(dir,1);
        iiy = iy + dirs(dir,2);
        if iix == nx+1
            nwalk = 0; %walker escaped
            iix = nx;
            ix1 = ix;
            iy1 = iy;
        end
        % Is the site there
        if(iix>0)
            if(iiy>0)
            if(iiy<ny+1)
                if(z(iix,iiy)>0)
                    ix = iix;
                    iy = iiy;
                    nfound = 1;
                    dir = dir +2;
                    if(dir>4)
                        dir = dir -4;
                    end
                end
            end
            end
        end
    end
end

nwalk = 1;
ix = ix0;
iy = iy0;
dir = 1; %1=left; 2 = down; 3 = right; 4 = up
right = zeros(nx,ny);
while(nwalk>0)
    right(ix,iy) = right(ix,iy) +1;
    nfound = 0;
    while (nfound==0)
        dir = dir+1;
        if (dir>4)
            dir = dir -4;
        end
        %check this direction
        iix = ix + dirs(dir,1);
        iiy = iy + dirs(dir,2);
        if (iix == nx+1)
            if (iy==iy1)
                nwalk = 0; %walker escaped
                iix = nx;
            end
        end
        %Is there a site here
        if(iix>0)
            if(iiy>0)
                if(iiy<ny+1)
                    if(iix<nx+1)
                        if(z(iix,iiy)>0)
                            ix = iix;
                            iy = iiy;
                            nfound = 1;
                            dir = dir -2;
                            if(dir<1)
                                dir = dir+4;
                            end
                        end
                    end
                end
            end
        end
    end
end

