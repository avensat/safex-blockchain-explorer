//
// Created by igor on 17.8.18..
//

#include "display_types.h"

namespace xmreg {

public_key const &get_public_key(displayable_output const &d_out)
{
    struct visitor : public boost::static_visitor<public_key const &> {
        public_key const &operator()(const txout_to_key &txin) const
        {
            return txin.key;
        }

        public_key const &operator()(const txout_token_to_key &txin) const
        {
            return txin.key;
        }
    };
    return boost::apply_visitor(visitor{}, d_out);
}

key_image const &get_key_image(displayable_input const &d_in)
{
    struct visitor : public boost::static_visitor<key_image const &> {
        key_image const &operator()(const txin_to_key &txin) const
        {
            return txin.k_image;
        }

        key_image const &operator()(const txin_token_to_key &txin) const
        {
            return txin.k_image;
        }

        key_image const &operator()(const txin_token_migration &txin) const
        {
            return txin.k_image;
        }
    };
    return boost::apply_visitor(visitor{}, d_in);
}

uint64_t get_amount(displayable_input const &d_in)
{
    struct visitor : public boost::static_visitor<uint64_t> {
        uint64_t operator()(const txin_to_key &txin) const
        {
            return txin.amount;
        }

        uint64_t operator()(const txin_token_to_key &txin) const
        {
            return txin.token_amount;
        }

        uint64_t operator()(const txin_token_migration &txin) const
        {
            return txin.token_amount;
        }
    };
    return boost::apply_visitor(visitor{}, d_in);
}

std::vector<uint64_t> const &get_key_offsets(displayable_input const &d_in)
{
    static std::vector<uint64_t> empty{};
    struct visitor
            : public boost::static_visitor<std::vector<uint64_t> const &> {
        std::vector<uint64_t> const &operator()(const txin_to_key &txin) const
        {
            return txin.key_offsets;
        }

        std::vector<uint64_t> const &
        operator()(const txin_token_to_key &txin) const
        {
            return txin.key_offsets;
        }

        std::vector<uint64_t> const &
        operator()(const txin_token_migration &txin) const
        {
            return empty;
        }
    };
    return boost::apply_visitor(visitor{}, d_in);
}

tx_out_type get_out_type(displayable_input const &d_in)
{
    struct visitor : public boost::static_visitor<tx_out_type> {
        tx_out_type operator()(const txin_to_key &txin) const
        {
            return tx_out_type::out_cash;
        }

        tx_out_type operator()(const txin_token_to_key &txin) const
        {
            return tx_out_type::out_token;
        }

        tx_out_type operator()(const txin_token_migration &txin) const
        {
            return tx_out_type::out_token;
        }
    };
    return boost::apply_visitor(visitor{}, d_in);
}

tx_out_type get_out_type(displayable_output const &d_in)
{
    struct visitor : public boost::static_visitor<tx_out_type> {
        tx_out_type operator()(const txout_to_key &txin) const
        {
            return tx_out_type::out_cash;
        }

        tx_out_type operator()(const txout_token_to_key &txin) const
        {
            return tx_out_type::out_token;
        }
    };
    return boost::apply_visitor(visitor{}, d_in);
}

boost::optional<crypto::hash const &> get_bitcoin_hash(displayable_input const &d_in)
{
    struct visitor : public boost::static_visitor<boost::optional<crypto::hash const &>> {
        boost::optional<crypto::hash const &> operator()(const txin_to_key &txin) const
        {
            return {};
        }

        boost::optional<crypto::hash const &> operator()(const txin_token_to_key &txin) const
        {
            return {};
        }

        boost::optional<crypto::hash const &> operator()(const txin_token_migration &txin) const
        {
            return txin.bitcoin_burn_transaction;
        }
    };
    return boost::apply_visitor(visitor{}, d_in);
}

std::string const &get_type_string(displayable_input const &d_in)
{
    static std::string cash{"cash"};
    static std::string token{"token"};
    static std::string migration{"migration"};

    struct visitor : public boost::static_visitor<std::string const &> {
        std::string const &operator()(const txin_to_key &) const
        {
            return cash;
        }

        std::string const &operator()(const txin_token_to_key &) const
        {
            return token;
        }

        std::string const &operator()(const txin_token_migration &) const
        {
            return migration;
        }
    };
    return boost::apply_visitor(visitor{}, d_in);
}

}