<?php

declare(strict_types=1);

const VLC_HANDLE_CLASSES = [
    'libvlc_instance_t', 'libvlc_media_t', 'libvlc_media_player_t', 'libvlc_media_list_t', 'libvlc_media_list_player_t',
    'libvlc_media_library_t', 'libvlc_media_discoverer_t', 'libvlc_renderer_discoverer_t', 'libvlc_renderer_item_t',
    'libvlc_event_manager_t', 'libvlc_equalizer_t', 'libvlc_log_t', 'libvlc_dialog_id',
];

const VLC_LIST_ELEMENT_CLASSES = [
    'libvlc_audio_output_t', 'libvlc_audio_output_device_t', 'libvlc_track_description_t', 'libvlc_module_description_t',
    'libvlc_media_track_t', 'libvlc_audio_track_t', 'libvlc_video_track_t', 'libvlc_subtitle_track_t',
    'libvlc_title_description_t', 'libvlc_chapter_description_t', 'libvlc_media_slave_t',
    'libvlc_media_discoverer_description_t', 'libvlc_rd_description_t',
];

it('makes every handle class final, not constructable, not cloneable, not serializable', function (string $class): void {
    $reflection = new ReflectionClass($class);

    $handle = $class::fromPointer(1);   // never dereferenced: serialize() only reads the class

    expect($reflection->isFinal())->toBeTrue()
        ->and($reflection->getConstructor()->isPrivate())->toBeTrue()
        ->and($reflection->isCloneable())->toBeFalse()
        ->and($class::fromPointer(0))->toBeNull()
        ->and(fn () => serialize($handle))->toThrow(Exception::class, 'is not allowed');
})->with([...VLC_HANDLE_CLASSES, ...VLC_LIST_ELEMENT_CLASSES]);

it('gives one PHP object per native address', function (): void {
    $a = libvlc_media_t::fromPointer(0x1000);

    expect(libvlc_media_t::fromPointer(0x1000))->toBe($a)
        ->and($a->pointer())->toBe(0x1000);
});

it('declares the C fields of each list element, in C order, read-only', function (): void {
    $fields = fn (string $class): array => array_map(fn (ReflectionProperty $p): string => $p->getName(), (new ReflectionClass($class))->getProperties());

    expect($fields('libvlc_audio_output_t'))->toBe(['psz_name', 'psz_description', 'p_next'])
        ->and($fields('libvlc_media_track_t'))->toBe(['i_codec', 'i_original_fourcc', 'i_id', 'i_type', 'i_profile', 'i_level', 'audio', 'video', 'subtitle', 'i_bitrate', 'psz_language', 'psz_description'])
        ->and($fields('libvlc_video_track_t'))->toBe(['i_height', 'i_width', 'i_sar_num', 'i_sar_den', 'i_frame_rate_num', 'i_frame_rate_den', 'i_orientation', 'i_projection', 'pose'])
        ->and($fields('libvlc_chapter_description_t'))->toBe(['i_time_offset', 'i_duration', 'psz_name'])
        ->and((new ReflectionProperty('libvlc_audio_output_t', 'psz_name'))->isReadOnly())->toBeTrue();
});

it('makes value structs with zero fields', function (): void {
    $viewpoint = new libvlc_video_viewpoint_t();
    $stats = new libvlc_media_stats_t();
    $event = new libvlc_event_t();

    expect([$viewpoint->f_yaw, $viewpoint->f_pitch, $viewpoint->f_roll, $viewpoint->f_field_of_view])->toBe([0.0, 0.0, 0.0, 0.0])
        ->and($stats->i_read_bytes)->toBe(0)
        ->and($stats->f_send_bitrate)->toBe(0.0)
        ->and($event->type)->toBe(0)
        ->and($event->p_obj)->toBe(0)
        ->and($event->u)->toBeNull();
});
