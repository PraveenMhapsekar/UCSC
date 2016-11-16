int len;
char buf[4096];
struct iovec iov = { buf, sizeof(buf) };
struct sockaddr_nl sa;
struct msghdr msg;
struct nlmsghdr *nh;

msg = { (void *)&sa, sizeof(sa), &iov, 1, NULL, 0, 0 };
len = recvmsg (fd, &msg, 0);

for (nh = (struct nlmsghdr *) buf; NLMSG_OK (nh, len);
     nh = NLMSG_NEXT (nh, len)) {
    /* The end of multipart message. */
    if (nh->nlmsg_type == NLMSG_DONE)
        return;

   if (nh->nlmsg_type == NLMSG_ERROR)
        /* Do some error handling. */
    ...

   /* Continue with parsing payload. */
    ...
}


