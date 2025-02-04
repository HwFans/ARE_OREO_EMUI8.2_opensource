#ifndef CGROUP_WORKINGSET_H_INCLUDED
#define CGROUP_WORKINGSET_H_INCLUDED

#include <linux/fs.h>
#include <linux/atomic.h>
#include <linux/cgroup.h>
#include <linux/pagemap.h>

extern void workingset_pagecache_record(struct file *file, pgoff_t start_offset, unsigned count);

static inline void workingset_pagecache_on_pagefault(struct file *file, pgoff_t start_offset)
{
	if (likely(task_css_is_root(current, workingset_cgrp_id)))
		return;

	workingset_pagecache_record(file, start_offset, 1);
}

static inline void workingset_pagecache_on_readfile(struct file *file, loff_t *pos, pgoff_t index, unsigned long offset)
{
	pgoff_t start_offset, end_offset;

	if (likely(task_css_is_root(current, workingset_cgrp_id)))
		return;

	if (*pos >= ((loff_t)index << PAGE_CACHE_SHIFT) + offset)
		return;

	start_offset = *pos >> PAGE_CACHE_SHIFT;
	end_offset = index + (offset >> PAGE_CACHE_SHIFT);
	workingset_pagecache_record(file, start_offset, end_offset - start_offset + 1);
}
#endif /* CGROUP_WORKINGSET_H_INCLUDED */
