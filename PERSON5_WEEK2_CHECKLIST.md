# Person 5 - Week 2 Checklist

Checklist này ghi lại các bước cần kiểm tra khi syscall truyền dữ liệu giữa
user space và kernel space.

## Phần đã làm trong Week 2

- [x] Kiểm tra `caller` trước khi gọi syscall.
- [x] Kiểm tra process đã liên kết với kernel hay chưa.
- [x] Từ chối PID bằng 0.
- [x] Kiểm tra con trỏ `krnl` và `regs` trong syscall dispatcher.
- [x] Trả lỗi khi syscall number chưa được hỗ trợ.
- [x] Khởi tạo `sc_regs` về 0 để tránh dữ liệu rác.
- [x] Truyền PID, syscall number và các tham số vào kernel.
- [x] Viết test cho quá trình truyền PID và syscall arguments.

## Cần kiểm tra khi làm phần memory protection

- [ ] Dùng PID để tìm đúng PCB của process gọi syscall.
- [ ] Kiểm tra địa chỉ user có thuộc vùng nhớ của process hay không.
- [ ] Từ chối địa chỉ chưa được map hoặc thuộc kernel space.
- [ ] Kiểm tra quyền đọc/ghi trước khi truy cập bộ nhớ.
- [ ] Kiểm tra toàn bộ vùng địa chỉ khi copy nhiều byte.
- [ ] Phát hiện trường hợp địa chỉ cộng kích thước bị overflow.
- [ ] Không copy một phần dữ liệu nếu validation thất bại.
- [ ] Trả lỗi từ paging hoặc memory operation về cho caller.

Các mục chưa hoàn thành sẽ được triển khai và test trong Week 3 sau khi nhóm
thống nhất cách quản lý PCB và ranh giới địa chỉ user/kernel.
