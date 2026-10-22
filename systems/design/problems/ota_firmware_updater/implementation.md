# One possible reference design

## Storage and trust

One possible 2,048 KiB layout is 64 KiB bootloader, two 832 KiB image slots and 320 KiB for redundant boot metadata, configuration/data and recovery bookkeeping. Verify erase boundaries, worst-case image headers/signatures and persistent-data requirements against the actual part before fixing addresses.

Assume the MCU supports execution from either slot; otherwise budget a power-fail-safe swap/copy strategy and its scratch requirements. The running image never erases its only confirmed recovery image.

A release signer produces authenticated metadata binding a cryptographic image digest, byte length, hardware IDs, bootloader/dependency constraints, version and security epoch. The bootloader verifies authenticity and policy from protected trust material before execution. Downloads go only to the inactive slot and cannot exceed its bounds. TLS is useful but does not replace image authentication. Define recovery authorization and a key-rotation procedure before revoking an old signing key.

## Device state machine

CONFIRMED → DOWNLOADING → VERIFIED → PENDING → TRIAL → CONFIRMED, with an explicit REVERT path. Journal metadata using two independently erasable records, sequence numbers and integrity checks; commit a new record only after its contents are durable. On startup choose a valid committed state, never partially written metadata. Verification must cover all bytes before marking pending.

Incomplete downloads are resumable only when chunks and image identity can be revalidated; otherwise discard them and retain the confirmed image. The loader validates the pending slot independently. Trial resets without confirmation revert after the documented attempt budget. A partially written confirmation leaves an earlier recoverable record rather than an ambiguous boot choice.

Do not irreversibly raise rollback protection during an unconfirmed trial. Coordinate the confirmed image record and security-counter update so reset at either step cannot strand the device. Once the security epoch advances, any permitted fallback must satisfy that epoch or use a separately authorized recovery path.

## Health and compatibility

Confirm only after local tests of essential peripherals, persistent data access, watchdog stability and the application's minimum useful operation. Network availability alone must not determine whether a healthy offline device can confirm. Keep trial writes compatible with the old firmware: use versioned records or shadow migration, and delay destructive schema changes until a recovery policy exists.

Validate hardware revision, dependency versions and bootloader support before installation. An authenticated image can still be incompatible or faulty.

## Fleet policy and failures

Start with lab devices, then representative canaries and progressively larger cohorts. Track crashes, failed trials, confirmation time, watchdog resets and application health against eligible/reporting devices and the previous release. Define automatic pause thresholds, minimum sample windows and a human recovery decision. Pausing delivery cannot recall an image from an offline device; local rollback must work independently.

Rate-limit retries, check power/storage before installation, and retain the selected manifest identity across reconnects. Threat-model a compromised application separately from a transport attacker; protect boot decisions and counters from unauthorized application writes.

Fault injection must cover every flash erase/write, metadata commit, first-boot reset, health-check failure and schema migration boundary.

Background: [MCUboot boot and upgrade design](https://docs.mcuboot.com/design.html) and [Trusted Firmware-M rollback protection](https://trustedfirmware-m.readthedocs.io/en/latest/design_docs/booting/secure_boot_rollback_protection.html). The architecture above is a practice scenario; actual storage and counter semantics depend on the selected bootloader and hardware.
