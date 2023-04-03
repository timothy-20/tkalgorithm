# 230331 - benchmark
## 개요
단일 연결 리스트 자료구조의 성능 테스트 결과를 기록한 readme입니다. 비교 대상은 **std::forward_list** 및 **tk::singly_linked_list**입니다.
주 목적은 **tk::singly_linked_list**의 resize 함수의 동작을 벤치마크 및 기록하기 위함입니다.

## 목적
**std::forward_list**의 resize 수준의 성능을 이끌어내는 것을 목표로 최적화 및 테스트를 진행하고 있습니다.

## 조건
하나의 기능에 대한 벤치마크는 10000번 반복되도록 설정해두었습니다.
container의 요소의 타입은 **int**입니다.

1. 기본 값으로 채워진 인스턴스 생성하는 경우
   - 1개의 요소를 가진 채 생성.
   - 10개의 요소를 가진 채 생성.
2. container가 가진 요소의 개수가 resize를 통해 추가되어야 할 요소의 개수보다 클 경우.
   - 9개의 요소에서 10개로 증가(최소치: 추가되어야 할 요소 1개).
   - 9개의 요소에서 17개로 증가(최대치: 추가되어야 할 요소 8개).
3. container가 가진 요소의 개수가 resize를 통해 추가되어야 할 요소의 개수보다 작을 경우.
   - 1개의 요소에서 9개로 증가.
   - 9개의 요소에서 19개로 증가.

## 환경
```text
프로세서: 1.4 GHz 쿼드 코어 Intel Core i5
그래픽: Intel Iris Plus Graphics 645 1536 MB
메모리: 16GB 2133 MHz LPDDR3
macOS: 13.3 베타(22E5219e)
```

## 결과
### **경우 1**의 벤치마크에 대한 결과
- 첫 번째 시도
```text
2023-03-31T09:57:00+09:00
Running /Users/imjeong-un/CLionProjects/tkalgorithm/cmake-build-debug/benchmark/benchmarks
Run on (8 X 1400 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB
  L1 Instruction 32 KiB
  L2 Unified 256 KiB (x4)
  L3 Unified 6144 KiB
Load Average: 4.65, 4.33, 3.93
***WARNING*** Library was built as DEBUG. Timings may be affected.
------------------------------------------------------------------------------------------------------------
Benchmark                                                                  Time             CPU   Iterations
------------------------------------------------------------------------------------------------------------
benchmark_singly_linked_list/std_constructor_001/iterations:10000        276 ns          276 ns        10000
benchmark_singly_linked_list/std_constructor_002/iterations:10000       1585 ns         1567 ns        10000
benchmark_singly_linked_list/tk_constructor_001/iterations:10000         357 ns          357 ns        10000
benchmark_singly_linked_list/tk_constructor_002/iterations:10000        2171 ns         2136 ns        10000
```
정말 압도적으로 느립니다. 생성자 내부에서 개수에 대해 n번 발생하는 push_front 함수에 영향이 있을 것으로 사료됩니다.

- 두 번째 시도
```c++
template <typename t>
 singly_linked_list<t>::singly_linked_list(size_t count, const t &value) :
 _before_front(std::make_unique<node>()),
 _back(nullptr),
 _level(0) {
     for (int i(0); i < count; i++) {
         if (i == 0) {
             this->_before_front->_next = std::make_unique<node>(value);
             this->_back = this->_before_front->_next.get();

         } else {
             this->_back->_next = std::make_unique<node>(value);
             this->_back = this->_back->_next.get();
         }

         this->_level++;
     }
 }
```
위와 같이 생성자 내부 로직을 수정해 보았습니다.

```text
2023-03-31T10:31:46+09:00
Running /Users/imjeong-un/CLionProjects/tkalgorithm/cmake-build-debug/benchmark/benchmarks
Run on (8 X 1400 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB
  L1 Instruction 32 KiB
  L2 Unified 256 KiB (x4)
  L3 Unified 6144 KiB
Load Average: 3.90, 4.01, 4.02
***WARNING*** Library was built as DEBUG. Timings may be affected.
------------------------------------------------------------------------------------------------------------
Benchmark                                                                  Time             CPU   Iterations
------------------------------------------------------------------------------------------------------------
benchmark_singly_linked_list/std_constructor_001/iterations:10000        198 ns          199 ns        10000
benchmark_singly_linked_list/std_constructor_002/iterations:10000       1176 ns         1170 ns        10000
benchmark_singly_linked_list/tk_constructor_001/iterations:10000         276 ns          276 ns        10000
benchmark_singly_linked_list/tk_constructor_002/iterations:10000        1708 ns         1691 ns        10000
```
push_front 함수 대신, 생성자 자체에서 요소 갯수만큼 반복하며 노드를 추가하는 작업을 진행하였습니다. 그러나 향상된 점은 없었습니다.

- 세 번째 시도
```c++
template <typename t>
class dummy {
private:
    struct node {
        t _value;
        node* _next;

        explicit node(t const& value = t()) :
        _value(value),
        _next(nullptr) {}
    };

private:
    node* _before_front;
    node* _back;
    size_t _level;

public:
    explicit dummy(size_t n, t const& value = t()) :
    _before_front(new node()),
    _back(nullptr),
    _level(0) {
        for (int i(0); i < n; i++) {
            if (this->_before_front->_next == nullptr) {
                this->_before_front->_next = std::move(new node(value));
                this->_back = this->_before_front->_next;

            } else {
                auto new_node(new node(value));
                new_node->_next = this->_before_front->_next;
                this->_before_front->_next = new_node;
            }

            this->_level++;
        }
    }
    ~dummy() {
        auto current(this->_before_front);

        while (current) {
            auto temp(current->_next);
            delete current;
            current = temp;
        }
    }
};
```
스마트 포인터인 **std::unique_ptr**를 이용하여 노드들을 관리하고 있습니다. 혹시 이로 인해 성능이 느린 것이 아닐까 생각하여 **dummy_singly_linked_list** 클래스를 구성하여
벤치마크를 진행해 보았습니다.

```text
2023-03-31T10:59:50+09:00
Running /Users/imjeong-un/CLionProjects/tkalgorithm/cmake-build-debug/benchmark/benchmarks
Run on (8 X 1400 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB
  L1 Instruction 32 KiB
  L2 Unified 256 KiB (x4)
  L3 Unified 6144 KiB
Load Average: 3.97, 3.29, 3.50
***WARNING*** Library was built as DEBUG. Timings may be affected.
--------------------------------------------------------------------------------------------------------------
Benchmark                                                                    Time             CPU   Iterations
--------------------------------------------------------------------------------------------------------------
benchmark_singly_linked_list/std_constructor_001/iterations:10000          301 ns          298 ns        10000
benchmark_singly_linked_list/std_constructor_002/iterations:10000         1619 ns         1579 ns        10000
benchmark_singly_linked_list/tk_constructor_001/iterations:10000           459 ns          457 ns        10000
benchmark_singly_linked_list/tk_constructor_002/iterations:10000          2856 ns         2761 ns        10000
benchmark_singly_linked_list/dummy_constructor_001/iterations:10000        161 ns          160 ns        10000
benchmark_singly_linked_list/dummy_constructor_002/iterations:10000        985 ns          856 ns        10000
```
스마트 포인터로 필드를 구성하지 않는 dummy_singly_linked_list 클래스는 무척이나 빨랐습니다. 몇 번의 추가적인 벤치마크 결과 후,
> tk::singly_linked_list > std::forward_list > dummy_singly_linked_list

위와 같은 순서로 실행 속도의 차이를 보였습니다.

이 시점에서 저는 제가 std::unique_ptr를 이용하여 구현했던 **tk::singly_linked_list**의 설계에 대해서 다시 한 번 고민했습니다.
심지어 해당 구현에서 생성자에게 넘기는 요소의 갯수가 100만개 이상인 경우에 잘못된 메모리 참조에 대한 에러가 발생했었습니다(제가 잘못 구현했을 가능성이 큽니다).

std::forward_list 내부에서는 스마트 포인터를 사용하지 않고 별도의 방법으로 메모리 관리를 수행하는 것으로 보입니다. 
> ```c++
> template < class T, class Alloc = allocator<T> >
> ```
> **std::forward_list**의 제네릭 템플릿 2번째 인자에 단서가 있을지도 모르겠습니다.

따라서 스마트 포인터를 사용하는 대신 메모리에 대한 안정성을 추가하는 구현을 통해 **tk::singly_linked_list**를 구현하는 방향을 고려해봐야겠습니다.

### **경우 2**의 벤치마크에 대한 결과
