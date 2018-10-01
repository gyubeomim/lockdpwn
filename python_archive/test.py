import pypcd

pc = pypcd.PointCloud.from_path('./1536323081575586.pcd')

bin_ = []

for i in range(pc.pc_data.size):
    if pc.pc_data[i][0] == 0 and pc.pc_data[i][1] == 0 and pc.pc_data[i][2] == 0 and pc.pc_data[i][3] == 0 and pc.pc_data[i][4] == 0:
        continue
    else:
        bin_.append([pc.pc_data[i][0],pc.pc_data[i][1],pc.pc_data[i][2],pc.pc_data[i][3]])



bin_np = np.array(bin_).reshape(-1)

fp = open('./test.bin', 'wb')
fp.write(bin_np)
