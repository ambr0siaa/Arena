# Arena Allocator

Simple linear allocater as a learning project. This project also implemted for my [virtual machine](https://github.com/ambr0siaa/LunaVM)

## API

* `arena_free`      clean up arena
* `arena_reset`     shift `alloc_pos` to start at all regions (don't free arena) 
* `arena_alloc`     allocate size bytes with alignement (aligment by size of `void*`)
* `arena_realloc`   reallocate pointer to new size