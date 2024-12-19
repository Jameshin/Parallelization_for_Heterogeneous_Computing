import multiprocessing as mp

# counting available cpu
# print(mp.cpu_count())


def f(n, rep):
    j = 0
    for i in range(rep):
        j += i

import time
def main():
    # set_start_method function은 interpreter process 생성, 이후 리스소 핸들링을 위한 handler를 call
    rep = 100000000
    mp.set_start_method('spawn')
    start = time.time()
    print("start process")
    p1 = mp.Process(target=f, args=(1,rep))
    p2 = mp.Process(target=f, args=(2,rep))

    p1.start()
    p2.start()

    p1.join()
    p2.join()
    end = time.time()
    print("time : {}".format(end-start))
    pr = end-start
    start = time.time()
    print("start normal")
    f(3, rep)
    f(4, rep)
    end = time.time()
    print("time : {}".format(end-start))
    npr = end-start
    print('process time - normal time : {}'.format(pr - npr))
if __name__=='__main__':
    main()