struct nlmsghdr *nh;    /* The nlmsghdr with payload to send. */
struct sockaddr_nl sa;
struct iovec iov = { (void *) nh, nh->nlmsg_len };
struct msghdr msg;

msg = { (void *)&sa, sizeof(sa), &iov, 1, NULL, 0, 0 };
memset (&sa, 0, sizeof(sa));
sa.nl_family = AF_NETLINK;
nh->nlmsg_pid = 0;
nh->nlmsg_seq = ++sequence_number;
/* Request an ack from kernel by setting NLM_F_ACK. */
nh->nlmsg_flags |= NLM_F_ACK;

sendmsg (fd, &msg, 0);
