#ifndef DRIP_VERSION_H
#define DRIP_VERSION_H

/**
 * @file version.h
 * @brief Library version information.
 *
 * @see https://semver.org/
 */

#define DRIP_VERSION_MAJOR 0
#define DRIP_VERSION_MINOR 1
#define DRIP_VERSION_PATCH 0
#define DRIP_VERSION_STRING "0.1.0-dev"

/**
 * @brief Get the library version as a string.
 *
 * @return Version string in "major.minor.patch" format.
 */
const char *drip_version_to_string(void);

#endif /* DRIP_VERSION_H */
