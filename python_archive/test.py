import os

image_set_file = os.path.join('../data/ImageSet/train.txt')

with open(image_set_file) as f:
   image_idx = [x.strip() for x in f.readlines()]

perm_idx = [image_idx[i] for i in
      np.random.permutation(np.arange(len(image_idx)))]

BATCH_SIZE = 32
cur_idx = 0

batch_idx = perm_idx[cur_idx:cur_idx + BATCH_SIZE]

for idx in batch_idx:
	print(idx)

'''
result :
        2011_09_26_0056_0000000126
        2011_09_26_0011_0000000223
        2011_09_26_0009_0000000407
        2011_09_26_0020_0000000065
        2011_09_26_0022_0000000797
        ...
'''
