#### How to compile:
```sudo clang -O2 -target bpf -c {{xdp_util}}.c -o {{xdp_util}}.o```

#### How to use XDP utils:

**Load XDP util:** \
```sudo ip link set dev {{ifname}} xdp obj {{xdp_util}}}.o ```

**Unload XDP util:** \
```sudo ip link set dev {{ifname}} xdp off```
 
**How to test:** \
```python3 /tests/ipip_sender.py {{inner_ip_dst}} {{outer_ip_dst}}```