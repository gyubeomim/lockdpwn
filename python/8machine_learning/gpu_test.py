import os 
from tensorflow.python.client import device_lib
import argparse 





def check_gpu_num(args):
    os.environ["CUDA_VISIBLE_DEVICES"] = args.device

    def get_available_gpus():
        local_device_protos = device_lib.list_local_devices()
        print(local_device_protos)
        return [x.name for x in local_device_protos if x.device_type == 'GPU']


    NGPU = len(get_available_gpus())
    print("GPU_TotalNum: ", NGPU)




def main(args):
    check_gpu_num(args)




if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
            '--device',
            type=str,
            default='0',
            help='GPU device number to run')
    args = parser.parse_args()


    main(args)
