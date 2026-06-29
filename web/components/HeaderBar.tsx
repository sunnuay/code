interface HeaderBarProps {
  title: string;
  error: string | null;
  message: string | null;
}

const HeaderBar = ({ title, error, message }: HeaderBarProps) => (
  <header className="flex h-14 flex-shrink-0 items-center gap-4 border-b border-gray-100 bg-white px-6">
    <h2 className="text-sm font-semibold text-black">{title}</h2>
    <div className="flex-1" />
    {error && (
      <span className="rounded-full bg-red-50 px-2.5 py-1 text-xs text-red-600">
        {error}
      </span>
    )}
    {message && (
      <span className="rounded-full border border-gray-200 bg-gray-50 px-2.5 py-1 text-xs text-gray-600">
        {message}
      </span>
    )}
  </header>
);

export default HeaderBar;
