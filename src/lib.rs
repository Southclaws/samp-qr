mod plugin;

use crate::plugin::Plugin;
use samp::initialize_plugin;

initialize_plugin!(natives: [Plugin::qr_get_matrix], {
    let samp_logger = samp::plugin::logger().level(log::LevelFilter::Info);

    samp::encoding::set_default_encoding(samp::encoding::WINDOWS_1251);

    let _ = fern::Dispatch::new()
        .format(|callback, message, record| {
            callback.finish(format_args!(
                "[samp-qr] [{}]: {}",
                record.level().to_string().to_lowercase(),
                message
            ))
        })
        .chain(samp_logger)
        .apply();

    Plugin {}
});
