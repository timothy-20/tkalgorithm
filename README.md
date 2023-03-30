# tkalgorithm
cpp를 사용하여 직접 구현한 자료구조 및 알고리즘을 cmake 프로젝트로 구성하였습니다.

google test 및 google benchmark 외부 라이브러리를 이용하여 단위 테스트 및 벤치마크를 구성하였습니다.
[TDD 방법론](https://ko.wikipedia.org/wiki/%ED%85%8C%EC%8A%A4%ED%8A%B8_%EC%A3%BC%EB%8F%84_%EA%B0%9C%EB%B0%9C)을 지향하고 있으며, 이를 통해 90% 이상의 테스트 커버리지를 목표로 삼고 있습니다.

doxygen 외부 라이브러리를 이용하여 문서화를 진행할 예정입니다.

## data structure
### singly_linked_list
요소 추가 시, 전방 삽입의 경우 O(1)의 복잡도를 가지는 기본적인 연결 리스트 자료구조입니다. n번째 위치에 삽입 시 O(n) 만큼의 복잡도를 가집니다.
iterator를 지원하며 단방향 순회가 가능합니다.

### doubly_linked_list
양 끝 요소의 삽입 및 삭제의 경우 O(1)의 복잡도를 가지는 기본적인 연결 리스트 자료구조입니다. 컨테이너 중간의 요소에 접근 할 시 O(n/2) 만큼의 복잡도를 가집니다. 최악의 경우 O(n)입니다.
iterator를 지원하며 양방향 순회가 가능합니다.

### dynamic_array


## algorithm