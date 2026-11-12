<?php

/** @generate-class-entries */

/*
 * gen_stub.php declarations: PHP syntax needs a `{}` after each signature, and gen_stub turns each
 * one into arginfo. The implementations are in src/types.c.
 *
 * Handles hold a native pointer. fromPointer() trusts any non-zero address it is given: the
 * extension cannot check that an address is a live libvlc object of that type. Dropping a handle
 * does not release the native object.
 *
 * List elements are handles too: libvlc owns their memory until the list's *_release. Their
 * properties are the C struct's fields, read from the native struct on every access.
 */

/** @not-serializable */
final class libvlc_instance_t
{
    private function __construct() {}

    /** The libvlc_instance_t* address; 0 once released. */
    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** @not-serializable */
final class libvlc_media_t
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** @not-serializable */
final class libvlc_media_player_t
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** @not-serializable */
final class libvlc_media_list_t
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** @not-serializable */
final class libvlc_media_list_player_t
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** @not-serializable */
final class libvlc_media_library_t
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** @not-serializable */
final class libvlc_media_discoverer_t
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** @not-serializable */
final class libvlc_renderer_discoverer_t
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** @not-serializable */
final class libvlc_renderer_item_t
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** Belongs to its parent (instance, media, player, list, list player, discoverers): released with it. @not-serializable */
final class libvlc_event_manager_t
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** @not-serializable */
final class libvlc_equalizer_t
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** Valid only inside the log callable that receives it. @not-serializable */
final class libvlc_log_t
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** Valid until the dialog is answered or dismissed. @not-serializable */
final class libvlc_dialog_id
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** Element of libvlc_audio_output_list_get(). @not-serializable */
final class libvlc_audio_output_t
{
    public readonly ?string $psz_name;
    public readonly ?string $psz_description;
    public readonly ?libvlc_audio_output_t $p_next;

    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** Element of libvlc_audio_output_device_list_get() / libvlc_audio_output_device_enum(). @not-serializable */
final class libvlc_audio_output_device_t
{
    public readonly ?libvlc_audio_output_device_t $p_next;
    public readonly ?string $psz_device;
    public readonly ?string $psz_description;

    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** Element of the track description lists. @not-serializable */
final class libvlc_track_description_t
{
    public readonly int $i_id;
    public readonly ?string $psz_name;
    public readonly ?libvlc_track_description_t $p_next;

    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** Element of libvlc_audio_filter_list_get() / libvlc_video_filter_list_get(). @not-serializable */
final class libvlc_module_description_t
{
    public readonly ?string $psz_name;
    public readonly ?string $psz_shortname;
    public readonly ?string $psz_longname;
    public readonly ?string $psz_help;
    public readonly ?libvlc_module_description_t $p_next;

    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/**
 * Element of libvlc_media_tracks_get(). The C union is three properties: the member matching
 * i_type (libvlc_track_audio, _video, _text), the other two null.
 * @not-serializable
 */
final class libvlc_media_track_t
{
    public readonly int $i_codec;
    public readonly int $i_original_fourcc;
    public readonly int $i_id;
    public readonly int $i_type;
    public readonly int $i_profile;
    public readonly int $i_level;
    public readonly ?libvlc_audio_track_t $audio;
    public readonly ?libvlc_video_track_t $video;
    public readonly ?libvlc_subtitle_track_t $subtitle;
    public readonly int $i_bitrate;
    public readonly ?string $psz_language;
    public readonly ?string $psz_description;

    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** libvlc_media_track_t.audio. @not-serializable */
final class libvlc_audio_track_t
{
    public readonly int $i_channels;
    public readonly int $i_rate;

    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** libvlc_media_track_t.video. pose is a copy of the embedded struct. @not-serializable */
final class libvlc_video_track_t
{
    public readonly int $i_height;
    public readonly int $i_width;
    public readonly int $i_sar_num;
    public readonly int $i_sar_den;
    public readonly int $i_frame_rate_num;
    public readonly int $i_frame_rate_den;
    public readonly int $i_orientation;
    public readonly int $i_projection;
    public readonly libvlc_video_viewpoint_t $pose;

    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** libvlc_media_track_t.subtitle. @not-serializable */
final class libvlc_subtitle_track_t
{
    public readonly ?string $psz_encoding;

    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** Element of libvlc_media_player_get_full_title_descriptions(). @not-serializable */
final class libvlc_title_description_t
{
    public readonly int $i_duration;
    public readonly ?string $psz_name;
    public readonly int $i_flags;

    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** Element of libvlc_media_player_get_full_chapter_descriptions(). @not-serializable */
final class libvlc_chapter_description_t
{
    public readonly int $i_time_offset;
    public readonly int $i_duration;
    public readonly ?string $psz_name;

    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** Element of libvlc_media_slaves_get(). @not-serializable */
final class libvlc_media_slave_t
{
    public readonly ?string $psz_uri;
    public readonly int $i_type;
    public readonly int $i_priority;

    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** Element of libvlc_media_discoverer_list_get(). @not-serializable */
final class libvlc_media_discoverer_description_t
{
    public readonly ?string $psz_name;
    public readonly ?string $psz_longname;
    public readonly int $i_cat;

    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** Element of libvlc_renderer_discoverer_list_get(). @not-serializable */
final class libvlc_rd_description_t
{
    public readonly ?string $psz_name;
    public readonly ?string $psz_longname;

    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** Value struct. */
final class libvlc_video_viewpoint_t
{
    public float $f_yaw = 0.0;
    public float $f_pitch = 0.0;
    public float $f_roll = 0.0;
    public float $f_field_of_view = 0.0;
}

/** Value struct: libvlc_media_get_stats() fills it. */
final class libvlc_media_stats_t
{
    public int $i_read_bytes = 0;
    public float $f_input_bitrate = 0.0;
    public int $i_demux_read_bytes = 0;
    public float $f_demux_bitrate = 0.0;
    public int $i_demux_corrupted = 0;
    public int $i_demux_discontinuity = 0;
    public int $i_decoded_video = 0;
    public int $i_decoded_audio = 0;
    public int $i_displayed_pictures = 0;
    public int $i_lost_pictures = 0;
    public int $i_played_abuffers = 0;
    public int $i_lost_abuffers = 0;
    public int $i_sent_packets = 0;
    public int $i_sent_bytes = 0;
    public float $f_send_bitrate = 0.0;
}

/** Value struct for libvlc_dialog_set_callbacks(): one callable per C function pointer, null for none. */
final class libvlc_dialog_cbs
{
    public ?Closure $pf_display_error = null;
    public ?Closure $pf_display_login = null;
    public ?Closure $pf_display_question = null;
    public ?Closure $pf_display_progress = null;
    public ?Closure $pf_cancel = null;
    public ?Closure $pf_update_progress = null;
}

/**
 * Value struct handed to event callables. p_obj is the emitting object's address; u is the union
 * member for type, as an object with that member's fields, or null.
 */
final class libvlc_event_t
{
    public int $type = 0;
    public int $p_obj = 0;
    public ?object $u = null;
}
