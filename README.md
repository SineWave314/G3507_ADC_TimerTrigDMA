## MSPM0G3507 ADC定时器触发与DMA搬运测试

使用开发板：MSPM0G3507 LaunchPad

## 外设配置

### ADC0：

重复单通道，定时器事件触发，DMA搬运数据

启用重复模式，并将触发模式设为`Valid trigger will step to next memory conversion register`，使得每次转换需要触发，且不自动禁用转换

DMA在每次触发后，搬运1组16位数据

### ADC1：

重复2通道序列，定时器事件触发，启用FIFO，DMA搬运数据

启用重复模式，并将Mem0触发模式设为`Trigger will automatically step to next memory conversion register`，Mem1触发模式设为`Valid trigger will step to next memory conversion register`，使得每次触发按顺序自动转换2个通道，且不自动禁用转换

启用FIFO，将2通道数据压缩为32位

为充分使用FIFO，DMA使用Mem11触发，在每次触发后，搬运6组32位数据（即Mem0~11的全部数据）
