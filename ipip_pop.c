#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <stdint.h>

#define htons(x) ((__be16)___constant_swab16((x)))

SEC("prog")

int xdp_pop_ipip(struct xdp_md *ctx) {
  void *data = (void *)(long)ctx->data;
  void *data_end = (void *)(long)ctx->data_end;
  struct ethhdr *eth = data;

  if (data + sizeof(struct ethhdr) + sizeof(struct iphdr) > data_end) {
    return XDP_PASS;
  }

  if (eth->h_proto == htons(ETH_P_IP)) {
    struct iphdr *iph = data + sizeof(struct ethhdr);

    if (iph->protocol == IPPROTO_IPIP) {
      struct ethhdr *neth = data + sizeof(struct iphdr);

      *neth = *eth;
      bpf_xdp_adjust_head(ctx, (int)sizeof(struct iphdr));
      return XDP_PASS;
    }
  }
  return XDP_PASS;
}