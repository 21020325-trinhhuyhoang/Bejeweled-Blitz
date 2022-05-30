# Bejeweled Blitz
Game Xếp kim cương viết bằng ngôn ngữ C++ sử dụng thư viện đồ họa SDL2
***
## Mục lục  
[Hướng dẫn cài đặt](#hướng-dẫn-cài-đặt)  
[Mô tả chung](#mô-tả-chung)  
[Các chức năng chính](#các-chức-năng-chính)  
[Các kỹ thuật được sử dụng](#các-kỹ-thuật-được-sử-dụng)  
[Tổng kết](#tổng-kết)  
***
## Hướng dẫn cài đặt
- Mở folder bạn muốn chứa game trong **_VSCode_**.
- Mở **_terminal_**.
- Clone repo về bằng lệnh
```
git clone https://github.com/21020325-trinhhuyhoang/Bejeweled-Blitz.git
```
- Mở folder **_Bejeweled-Blitz_** bằng lệnh 
```
cd Bejeweled-Blitz
```
- Để chạy game sử dụng câu lệnh
```
.\main.exe
```
***
## Mô tả chung
- **Bối cảnh**:

  _Ở một ngọn núi có rất nhiều đá quý nhưng cùng với đó là những quả bom. Bạn phải tìm cách lấy được nhiều ngọc nhanh nhất có thể .Vì khi những quả bom phát nổ, chúng sẽ phá hủy hết số ngọc còn lại._
- **Cách chơi**: hoán đổi hai viên ngọc liền kề để tạo thành hàng các viên ngọc cùng loại liên tiếp và phải gỡ những quả bom hẹn giờ trước khi chúng nổ.
- **Ý tưởng chính**: làm lại game _Bejeweled_ cổ điển với những cải tiến giúp game mới lạ hơn:
  - Game over khi bom hẹn giờ nổ.
  - Càng về sau bom hẹn giờ càng dày đặc và thời gian nổ càng ngắn hơn.
  - Thêm hiệu ứng khi xếp các hàng đặc biệt.
***
## Các chức năng chính
**_Video demo game: [Bejeweled Blitz](https://youtu.be/gr900ppeUNs)_**
- Hoán đổi hai viên ngọc liền kề tạo thành hàng 3 viên ngọc cùng loại, bạn sẽ lấy được chúng và các viên ngọc ở trên sẽ rơi xuống.
- Hoán đổi hai viên ngọc liền kề mà không tạo thành bất kì hàng 3 viên ngọc cùng loại nào, chúng sẽ về vị trí cũ.
- Xếp được thành các dạng hàng đặc biệt sẽ có hiệu ứng của riêng chúng.
- Trong một lượt, các lần liên tiếp tạo thành hàng sau sẽ được nhiều điểm hơn lần trước.
- Phải ngăn cho bom hẹn giờ nổ bằng cách lấy được viên ngọc gắn trên quả bom đó.
- Khi thời gian bom hẹn giờ về 0, nó sẽ phá hủy hết tất cả số ngọc còn lại và trò chơi sẽ kết thúc.
***
## Các kỹ thuật được sử dụng
- **Lập trình đồ họa và âm thanh** với thư viện _SDL2_ và các thư viện mở rộng _SDL_mixer_, _SDL_image_, _SDL_ttf_.
- **Xử lý bắt phím**.
- **Kỹ thuật lập trình hướng đối tượng**.
- **Kỹ thuật tách file**.
- **Các kỹ thuật khác**: con trỏ, mảng, kỹ thuật sinh số ngẫu nhiên,...
***
## Tổng kết
1. **Kết luận**:
- Game đã có các chức năng cơ bản của _Bejeweled_ cổ điển và thêm những cải tiến về cách chơi.
- Code khá sạch đẹp dễ hiểu, tuy nhiên vẫn còn nhiều điểm chưa tối ưu cần cải thiện và phát triển thêm.
2. **Hướng phát triển**:
- **Phát triển thêm các tính năng**:
  - Bảng xếp hạng: lưu tên và điểm của 5 người chơi được điểm cao nhất.
  - Bảng cài đặt: bật/tắt và chỉnh âm lượng, chơi lại, quay về menu,...
  - Nhiều chế độ chơi: mỗi chế độ có nhiều thử thách và mục tiêu thắng khác nhau.
  - Thao tác với chuột.
  - Chơi online để so điểm với bạn bè.
- **Phát triển âm thanh và đồ họa**:
  - Nâng cấp âm thanh và đồ họa sống động hơn.
  - Mỗi chế độ có khung cảnh và âm thanh khác nhau.
- **Hỗ trợ game chơi trên nhiều hệ điều hành**.
3. **Điều tâm đắc rút ra được sau khi hoàn thiện chương trình**:
- Dự án giúp mình biết cách tìm tài liệu để nâng cao trình độ code cho bản thân.
- Học thêm nhiều khiến thức mới:
  - Lập trình đồ họa, âm thanh bằng thư viện SDL2.
  - Lập trình hướng đối tượng và tách file.
- Tuy chỉ là một game đơn giản nhưng mình rất vui vì đã làm được một sản phẩm cá nhân.
