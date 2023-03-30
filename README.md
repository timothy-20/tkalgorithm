# tkalgorithm
직접 구현한 자료구조 및 알고리즘을 cmake를 사용해 정적 라이브러리로 구성해본 프로젝트입니다.

## data structure
### singly_linked_list
요소 추가 시, 전방 삽입의 경우 O(1)의 복잡도를 가지는 기본적인 연결 리스트 자료구조입니다. n번째 위치에 삽입 시 O(n) 만큼의 복잡도를 가집니다.
iterator를 지원하며 단방향 순회가 가능합니다.

### doubly_linked_list
양 끝 요소의 삽입 및 삭제의 경우 O(1)의 복잡도를 가지는 기본적인 연결 리스트 자료구조입니다. 컨테이너 중간의 요소에 접근 할 시 O(n/2) 만큼의 복잡도를 가집니다. 최악의 경우 O(n)입니다.
iterator를 지원하며 양방향 순회가 가능합니다.

### dynamic_array


## algorithm